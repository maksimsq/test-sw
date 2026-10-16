#!/bin/awk -f

NR == 12 {
    print $9, $8
}
