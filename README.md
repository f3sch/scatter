# PAD -- final project group 3 -- scatter

## Setup

```bash
$ git submodule init
$ git submodule update --recursive
$ ./vcpkg/bootstrap-vcpkg.sh -disableMetrics
$ cmake -DUSE_VCPKG=On --preset local
$ cmake --build --preset local
```

<!-- Or use the script: -->
<!-- ```bash -->
<!-- $ ./scripts/build.sh -->
<!-- ``` -->
