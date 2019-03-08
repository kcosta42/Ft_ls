# Ft_ls

Disclaimer
----------
> In School 42, almost every project must be written according to a coding syntax standard (also known as "[Norme](./docs/norme.fr.pdf)").
>
> That's why some parts may be strange

About
-----
>To know everything about the filesystem, how files and directories are stored, let's code one of the most used commands ourselves: `ls`

This is the first project of the Unix branch at School 42 Paris

Usage
-----
`./ft_ls [-1GRalrt] [file ...]`
* -1 : Force output to be one entry per line
* -G : Enable colorized output
* -R : Recursively list subdirectories encountered
* -a : Include directory entries whose names begin with a dot (.)
* -l : List in long format.
* -r : Reverse the order of the sort to get reverse lexicographical order or the oldest entries first (or largest files last, if combined with sort by size
* -t : Sort by time modified (most recently modified first) before sorting the operands by lexicographi-cal order

##### Project done in 2016
