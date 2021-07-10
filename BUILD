load("@io_bazel_rules_docker//cc:image.bzl", "cc_image")


cc_image(
    name = "app",
    srcs = ["main.cc"],
    deps = ["@com_github_gabime_spdlog//:spdlog"],
    linkopts = ["-lpthread"]
)
