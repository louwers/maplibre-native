workspace(name = "Maplibre")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "build_bazel_rules_apple",
    sha256 = "a95d9007570cb5c6180b7e380bad2a854734209cc02390eed208efb922843c8a",
    strip_prefix = "rules_apple-76752fe84ff0dc5d793033015647c78efbf41309",
    url = "https://github.com/bazelbuild/rules_apple/archive/76752fe84ff0dc5d793033015647c78efbf41309.tar.gz",
)

http_archive(
    name = "com_github_buildbuddy_io_rules_xcodeproj",
    sha256 = "1e2f40eaee520093343528ac9a4a9180b0500cdd83b1e5e2a95abc8c541686e2",
    url = "https://github.com/buildbuddy-io/rules_xcodeproj/releases/download/1.1.0/release.tar.gz",
)

load(
    "@com_github_buildbuddy_io_rules_xcodeproj//xcodeproj:repositories.bzl",
    "xcodeproj_rules_dependencies",
)

xcodeproj_rules_dependencies()

load(
    "@build_bazel_rules_apple//apple:repositories.bzl",
    "apple_rules_dependencies",
)

apple_rules_dependencies()

load(
    "@build_bazel_rules_swift//swift:repositories.bzl",
    "swift_rules_dependencies",
)

swift_rules_dependencies()

load(
    "@build_bazel_rules_swift//swift:extras.bzl",
    "swift_rules_extra_dependencies",
)

swift_rules_extra_dependencies()

load(
    "@build_bazel_apple_support//lib:repositories.bzl",
    "apple_support_dependencies",
)

apple_support_dependencies()
