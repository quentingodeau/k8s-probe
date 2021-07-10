workspace(name = "k8s-probe")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name ="com_github_fmtlib_fmt",
    urls = ["https://github.com/fmtlib/fmt/archive/refs/tags/7.1.3.tar.gz"],
    build_file= "//bazel:external/fmtlib.BUILD",
    strip_prefix = "fmt-7.1.3",
    sha256 = "5cae7072042b3043e12d53d50ef404bbb76949dad1de368d7f993a15c8c05ecc",
)

http_archive(
    name ="com_github_gabime_spdlog",
    urls = ["https://github.com/gabime/spdlog/archive/refs/tags/v1.8.5.tar.gz"],
    build_file= "//bazel:external/spdlog.BUILD",
    strip_prefix = "spdlog-1.8.5",
)

http_archive(
    name = "io_bazel_rules_docker",
    sha256 = "59d5b42ac315e7eadffa944e86e90c2990110a1c8075f1cd145f487e999d22b3",
    strip_prefix = "rules_docker-0.17.0",
    urls = ["https://github.com/bazelbuild/rules_docker/releases/download/v0.17.0/rules_docker-v0.17.0.tar.gz"],
)

load(
    "@io_bazel_rules_docker//repositories:repositories.bzl",
    container_repositories = "repositories",
)

container_repositories()

load(
    "@io_bazel_rules_docker//cc:image.bzl",
    _cc_image_repos = "repositories",
)

_cc_image_repos()