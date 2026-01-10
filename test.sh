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

default_ip='--ip 127.0.0.1'

run_test "--ports test (invalid)"       1  --ports test
run_test "--speedup test (invalid)"     1  --speedup test
run_test " --ports 1 (valid)"           0 $default_ip --ports 1
run_test "--speedup 1 (valid)"          0 $default_ip --speedup 1
run_test "--speedup 251 (invalid)"      1 $default_ip --speedup 251
run_test "--ports 65536 (invalid)"      1 $default_ip --ports 65536
run_test "--scan SYN (valid)"           0 $default_ip --scan SYN
run_test "--scan NULL (valid)"          0 $default_ip --scan NULL
run_test "--scan ACK (valid)"           0 $default_ip --scan ACK
run_test "--scan FIN (valid)"           0 $default_ip --scan FIN
run_test "--scan XMAS (valid)"          0 $default_ip --scan XMAS
run_test "--scan (invalid) aaaa"        1 $default_ip --scan aaa
run_test "--ip (valid) 8.8.8.8"         0 --ip 8.8.8.8
run_test "--ip (valid) google.com"      0 --ip google.com
run_test "--ip (invalid) nope"          1 --ip nope
run_test "(invalid) no IP"                    1 ""

run_test "--ports 1 $default_ip --speedup 250 --scan SYN" 0 --ports 1 $default_ip --speedup 250 --scan SYN