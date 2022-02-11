EXEC=$1
TMP_OUT=$2
echo "Entrei aquii"
for i in {5..5..1}; do
  testname_input=$(printf "0%01d-input.txt" $i)
  testname_output=$(printf "0%01d-output.txt" $i)
  echo $testname_input
  $EXEC < tests/$testname_input > $TMP_OUT
  if ! diff -qwB tests/$testname_output $TMP_OUT &>/dev/null; then
    echo "Test $testname_input failed"
  else
    echo "Test $testname_input passed"
  fi
done