load("@hedron_compile_commands//:refresh_compile_commands.bzl", "refresh_compile_commands")

refresh_compile_commands(
    name = "refresh_compile_commands",
    targets = {
        "//...:all": "",
    },
)

# compile culprit_set.cc and culprit_set.h
cc_binary(
    name = "culprit_set",
    srcs = [
        "culprit_set.cc",
        "culprit_set.h",
    ],
)
