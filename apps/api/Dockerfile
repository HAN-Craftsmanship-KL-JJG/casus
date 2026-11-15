# Builds the application server with Clang, CMake and vcpkg, and runs the unit tests.
FROM debian:13-slim AS build

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        autoconf automake ca-certificates clang cmake curl git libtool make ninja-build \
        perl pkg-config tar unzip zip \
    && rm -rf /var/lib/apt/lists/*

# VCPKG_FORCE_SYSTEM_BINARIES is needed on ARM, such as a Mac with Apple silicon.
ENV VCPKG_ROOT=/opt/vcpkg VCPKG_FORCE_SYSTEM_BINARIES=1 CC=clang CXX=clang++

# Keep the tag equal to `builtin-baseline` in vcpkg.json.
ARG VCPKG_TAG=2026.10.16
RUN git clone --depth 1 --branch "${VCPKG_TAG}" https://github.com/microsoft/vcpkg "${VCPKG_ROOT}" \
    && "${VCPKG_ROOT}/bootstrap-vcpkg.sh" -disableMetrics

WORKDIR /src

# Own layer: the libraries only rebuild when vcpkg.json changes.
COPY vcpkg.json ./
RUN "${VCPKG_ROOT}/vcpkg" install --x-install-root=build/vcpkg_installed --clean-after-build

# The same preset builds the application outside a container.
COPY CMakeLists.txt CMakePresets.json ./
COPY src ./src
COPY tests ./tests
RUN cmake --preset release \
    && cmake --build --preset release \
    && ctest --preset release

FROM debian:13-slim

COPY --from=build /src/build/icde-api /usr/local/bin/icde-api
USER 65534:65534
EXPOSE 8080
ENTRYPOINT ["/usr/local/bin/icde-api"]
