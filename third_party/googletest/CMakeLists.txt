# Google Test
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        I60fa4d4e7827516d317ce893377d1f72e49c6a2f # release-1.12.0
)

FetchContent_MakeAvailable(googletest)
