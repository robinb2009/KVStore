load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "file_test",
    srcs = ["file_test.cc"],
    deps = [
        "//main/utils:file",
        "//main/utils:test_util",
    ],
    timeout = "short",
)