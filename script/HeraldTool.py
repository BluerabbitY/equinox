import os, shutil, subprocess, argparse
from typing import List, Optional

def command_exist(cmd: str) -> bool:
    return shutil.which(cmd) is not None

def parse_args():
    parser = argparse.ArgumentParser(description="Toolset for Herald")

    group = parser.add_mutually_exclusive_group()
    group.add_argument('--setup', action='store_true', help='execute setup for Herald')
    group.add_argument('--update-dependent', action='store_true', help='update dependent for Herald')
    group.add_argument('--build-dependent', action='store_true', help='build dependent for Herald')
    group.add_argument('--build-clean', action='store_true', help='clean dependent build cache')
    group.add_argument('--build-deepclean', action='store_true', help='clean dependent build directory')

    parser.add_argument('--qt-prefix', type=str, help='qt prefix path that must be used with --setup')

    args = parser.parse_args()

    if args.setup and args.qt_prefix is not None:
        if args.qt_prefix.strip() == "":
            parser.error("--qt-prefix is empty")

    return args

def check_required_tools(tools):
    missing_deps = [dep for dep in tools if not command_exist(dep)]
    if missing_deps:
        print("Missing tools:", ', '.join(missing_deps))
        print("Please install the missing tools and try again.")
        exit(-1)

def is_git_repo(path) -> bool:
    try:
        subprocess.run(
            ["git", "-C", path, "status"],
            stdout=subprocess.DEVNULL,
            stderr=subprocess.DEVNULL,
            check=True
        )
        return True
    except subprocess.CalledProcessError:
        return False

def clone_repository(repo: str, branch: str, target: str):
    git_dir = os.path.join(target, ".git")
    if not os.path.exists(target):
        subprocess.run([
            "git", "clone", "--branch", branch, "--single-branch", "--recurse-submodules", repo, target
        ], check=True)
    elif os.path.exists(git_dir):
        subprocess.run([
            "git", "-C", target, "pull", "--recurse-submodules"
        ], check=True)
    else:
        raise Exception(f"The target directory '{target}' exists but is not a git repository.")

def build_and_install(source_dir: str, build_dir: str, install_prefix: str = None, cmake_options: Optional[List[str]] = None):
    abs_source = os.path.abspath(source_dir)
    abs_build = os.path.abspath(os.path.join(source_dir, build_dir))
    os.makedirs(abs_build, exist_ok=True)

    cmake_cmd = ["cmake", "-G", "Ninja"]

    if install_prefix:
        cmake_cmd.append(f"-DCMAKE_INSTALL_PREFIX={install_prefix}")

    if cmake_options:
        cmake_cmd.extend(cmake_options)

    cmake_cmd.append(abs_source)

    cmds = [
        cmake_cmd,
        ["ninja"],
        ["ninja", "install"]
    ]

    for cmd in cmds:
        print(f"Running: {' '.join(cmd)} in {abs_build}")
        subprocess.run(cmd, cwd=abs_build, check=True)

def clean_build_directory(build_dir: str):
    abs_build = os.path.abspath(build_dir)
    if os.path.exists(abs_build):
        shutil.rmtree(abs_build)
        print(f"Removed build directory: {abs_build}")
    else:
        print(f"Build directory does not exist: {abs_build}")

if __name__ == "__main__":
    scriptPath = os.path.dirname(os.path.abspath(__file__))
    projectPath = os.path.dirname(scriptPath)

    depDir = projectPath + "/src/dependencies"
    cacheDir = projectPath + "/.cache"
    installDir = depDir + "/install"

    configFile = cacheDir + "/herald.config"

    qt_prefix_path = ""

    allArgs = parse_args()

    if allArgs.setup:
        print("Start setup for Herald...")
        os.makedirs(cacheDir, exist_ok=True)
        with open(configFile, "w", encoding="utf-8") as f:
            f.write(allArgs.qt_prefix)
        qt_prefix_path = allArgs.qt_prefix
    else:
        with open(configFile, 'r', encoding='utf-8') as f:
            qt_prefix_path = f.readline()
            print("Qt prefix: ", qt_prefix_path)

    tasks = [
        # name, git url, branch, install dir, cmake options
        ("lib60870", "https://github.com/BluerabbitY/lib60870.git", "master", installDir, ["-DBUILD_EXAMPLES=OFF", "-DBUILD_TESTS=OFF"]),
        ("spdlog", "https://github.com/gabime/spdlog.git", "v1.x", None, ["-DSPDLOG_MASTER_PROJECT=OFF"]),
        ("HuskarUI", "https://github.com/mengps/HuskarUI.git", "master", installDir, ["-DBUILD_HUSKARUI_GALLERY=OFF", f"-DCMAKE_PREFIX_PATH={qt_prefix_path}"]),
    ]

    try:

        if allArgs.setup or allArgs.update_dependent:
            check_required_tools(['git'])
            # download dependent libraries
            for name, git_url, git_branch, install_dir, cmake_opt in tasks:
                clone_repository(git_url, git_branch, depDir + "/" + name)

        if allArgs.setup or allArgs.build_dependent:
            check_required_tools(['cmake', 'ninja'])
            # build and install dependent libraries
            for name, git_url, git_branch, install_dir, cmake_opt in tasks:
                build_and_install(depDir + "/" + name, cacheDir + "/" + name, install_dir, cmake_opt)

        if allArgs.build_clean:
            for name, git_url, git_branch, install_dir, cmake_opt in tasks:
                shutil.rmtree(depDir + "/" + name)

    except subprocess.CalledProcessError as e:
        print("Failed: ", e)
