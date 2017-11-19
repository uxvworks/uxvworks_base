# Copyright (c) <year> <author> (<email>)
# Distributed under the MIT License.
# See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT

# Set project source files.
set(SRC
  "${SRC_PATH}/factorial.cpp"
  "${SRC_PATH}/main_test.cpp"
  "${SRC_PATH}/cli_args.cpp"
  "${MODULE1_PATH}/factorial1.c"
  "${TERMBOX_PATH}/demo/keyboard.cpp"
  "${TERMBOX_PATH}/termbox.c"
  "${TERMBOX_PATH}/utf8.c"
)

# Set project main file.
set(MAIN_SRC
  "${SRC_PATH}/main_uv.cpp"
)

# Set project test source files.
set(TEST_SRC
  "${TEST_SRC_PATH}/testCppbase.cpp"
  "${TEST_SRC_PATH}/testFactorial.cpp"
)
