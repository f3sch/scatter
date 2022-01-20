#!/bin/bash

set -Eeuo pipefail
IFS=$'\n\t'

# Go to project directory
cd "$(dirname "${BASH_SOURCE[0]}")/.." > /dev/null 2>&1


# If availale load tools
if command -v spack &> /dev/null; then
  print_info "Loading development tools with Spack"
  spack load ninja
  spack load cmake@3.20
  spack load gcc@11
  spack load llvm@13
fi

# This bash function can be used to easily build our CMake presets.
build_preset() {
  local type="$1"
  echo "Building: ${type}"
  if [[ ! -d build/"${type}" ]]; then
    cmake --preset "${type}"
  fi
  cmake --build --preset "${type}"
}

# Install dependencies
install() {
  git submodule init
  git submodule update --recursive
  ./vcpkg/bootstrap-vcpkg.sh -disableMetrics
}

# Bash Menu
PS3='Please enter your choice: '
options=("local" "release" "skylake" "install" "Quit")
select opt in "${options[@]}"
do
    case $opt in
        "local")
                build_preset local
            ;;
        "release")
                build_preset release
            ;;
        "skylake")
                build_preset skylake
            ;;
        "install")
                install
            ;;
        "Quit")
            break
            ;;
        *)
                echo "invalid option $REPLY"
                break
            ;;
    esac
done
