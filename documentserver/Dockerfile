# Builds the document server with Clang, CMake and vcpkg, and runs the unit tests.
# Alpine, because the pandoc/typst image it runs in is Alpine.
FROM alpine:3.23 AS build

RUN apk add --no-cache \
        autoconf automake bash build-base ca-certificates clang cmake curl git libtool \
        linux-headers ninja-build perl pkgconf python3 tar unzip zip

# VCPKG_FORCE_SYSTEM_BINARIES is needed on Alpine.
ENV VCPKG_ROOT=/opt/vcpkg VCPKG_FORCE_SYSTEM_BINARIES=1 CC=clang CXX=clang++ \
    PATH="/usr/lib/ninja-build/bin:${PATH}"

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

# Pandoc and Typst come from the official image.
FROM pandoc/typst:3.8.3

RUN apk add --no-cache libstdc++
COPY --from=build /src/build/icde-documentserver /usr/local/bin/icde-documentserver
# Pandoc and Typst write their temporary files below HOME and TMPDIR.
ENV HOME=/tmp TMPDIR=/tmp
WORKDIR /tmp
USER 65534:65534
EXPOSE 8080
ENTRYPOINT ["/usr/local/bin/icde-documentserver"]
