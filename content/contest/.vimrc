set cin aw ai is si sts=2 sw=2 tm=50 nu noeb bg=dark ru cul
sy on
" Select region and then type :Hash to hash your selection.
" Useful for verifying that there aren't mistypes.
ca Hash w !cpp -dD -P -fpreprocessed \| tr -d '[:space:]' \| md5sum \| cut -c-6
colo desert
set popt+=number:y
