#!/bin/bash

# OUTFILE_VALGRIND=outfile_valgrind
# OUTFILE_MINISHELL=outfile_minishell
# OUTFILE_BASH=outfile_bash

# TEST_CASE=(
#     "ls"
#     "wrong_cmd sdsd"
#     "ls"
#     "asdjasfdl"

# )

# i=0
# for test in "${TEST_CASE[@]}"; do
#     valgrind ./minishell "$test" > "$OUTFILE_VALGRIND"
#     ./minishell "$test" > "$OUTFILE_MINISHELL"
#     ./bin/bash -c "$test" > "$OUTFILE_BASH"
#     if diff "$OUTFILE_MINISHELL" "$OUTFILE_BASH"; then
#         echo "$i.OK"
#     else
#         echo "$i.KO"
#     fi
#     ((i++))
# done
#!/bin/bash

OUTFILE_VALGRIND=outfile_valgrind
OUTFILE_MINISHELL=outfile_minishell
OUTFILE_BASH=outfile_bash

TEST_CASE=(
    "ls"
    "wrong_cmd"
    "ls -l"
    "asdjasfdl"
)

i=0
for test in "${TEST_CASE[@]}"; do
    echo "Testing case: $test"
    valgrind ./minishell "$test" > "$OUTFILE_VALGRIND" 2>&1
    ./minishell "$test" > "$OUTFILE_MINISHELL" 2>&1
    /bin/bash -c "$test" > "$OUTFILE_BASH" 2>&1
    if diff "$OUTFILE_MINISHELL" "$OUTFILE_BASH"; then
        echo "$i. OK"
    else
        echo "$i. KO"
        echo "Difference:"
        # diff "$OUTFILE_MINISHELL" "$OUTFILE_BASH"
    fi
    ((i++))
done
