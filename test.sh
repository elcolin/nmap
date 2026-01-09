#!/bin/bash

set -u

GREEN="\033[0;32m"
RED="\033[0;31m"
RESET="\033[0m"

run_test() {
    local description="$1"
    local expected_status="$2"
    shift 2

    ./ft_nmap "$@"
    status=$?

    if [ "$status" -eq "$expected_status" ]; then
        echo -e "${GREEN}PASS${RESET}: $description"
    else
        echo -e "${RED}FAIL${RESET}: $description (expected $expected_status, got $status)"
    fi
}

run_test "--ports test (invalid)"       1 --ports test
run_test "--speedup test (invalid)"     1 --speedup test
run_test "--ports 1 (valid)"            0 --ports 1
run_test "--speedup 1 (valid)"          0 --speedup 1
run_test "--speedup 251 (invalid)"       1 --speedup 251
run_test "--ports 65536 (invalid)"       1 --ports 65536
run_test "--scan SYN (valid)"           0 --scan SYN
run_test "--scan NULL (valid)"           0 --scan NULL
run_test "--scan ACK (valid)"           0 --scan ACK
run_test "--scan FIN (valid)"           0 --scan FIN
run_test "--scan XMAS (valid)"           0 --scan XMAS
run_test "--scan (invalid) aaaa"         1 --scan aaa
