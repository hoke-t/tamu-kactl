git pull https://github.com/kth-competitive-programming/kactl.git master
find . -name '*.h' ! -type d -exec bash -c 'expand -t 2 "$0" > /tmp/e && mv /tmp/e "$0"' {} \;
