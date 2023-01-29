#!/bin/bash
# sudo su gitlab-runner
# ssh-keygen -t rsa -b 2048
# ssh-copy-id orv2@172.24.116.8
# ssh orv2@172.24.116.8
scp src/cat/s21_cat orv2@172.24.116.8:~/
scp src/grep/s21_grep orv2@172.24.116.8:~/
ssh orv2@172.24.116.8 "echo "qwe" | sudo -S mv s21_cat s21_grep /usr/local/bin"
