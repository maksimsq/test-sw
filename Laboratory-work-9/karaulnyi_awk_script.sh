#!/bin/bash

ls -l | awk 'NR==12 {print $9, $8}'
