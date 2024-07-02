load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "kv_store_test",
    srcs = ["kv_store_test.cc"],
    deps = [
        "//main:kv_store",
        "@com_github_gflags_gflags//:gflags",
        "@com_github_google_glog//:glog",
        "@com_google_googletest//:gtest_main",
    ],
    timeout = "short",
)