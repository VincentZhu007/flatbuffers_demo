# Google Test
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        15460959cbbfa20e66ef0b5ab497367e47fc0a04 # release-1.12.0
)

FetchContent_MakeAvailable(googletest)
