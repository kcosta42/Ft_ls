/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 14:09:05 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/03 17:43:47 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"

static int	ft_usage(void)
{
	printf("usage: ./ft_ls directory file\n");
	return (1);
}

static int	ft_error(int errnum, const char *filename)
{
	if (filename)
		ft_printf("ft_ls: %s: %s\n", filename, strerror(errnum));
	else
		ft_printf("ft_ls: %s\n", strerror(errnum));
	return (errnum);
}

static int	ft_list_dir(const char *filename)
{
	DIR			*dirp;
	t_dirent	*entry;

	if (!(dirp = opendir(filename)))
		return (ft_error(errno, filename));
	while ((entry = readdir(dirp)))
	{
		ft_printf("d_ino: %llu\nd_reclen: %hu\nd_type: %hhu\nd_namlen: %hu\n\
d_name: %s\n", entry->d_ino, entry->d_reclen, entry->d_type,
				entry->d_namlen, entry->d_name);
	}
	if (closedir(dirp) == -1)
		return (ft_error(errno, filename));
	return (0);
}

static int	ft_inspect_file(const char *filename)
{
	t_stat		buf;
	t_passwd	*psw;
	t_group		*grp;


	if (lstat(filename, &buf) < 0)
		return (ft_error(errno, filename));
	ft_printf("st_dev: %d\nst_ino: %llu\nst_mode: %hu\nst_nlink: %hu\n\
st_uid: %u\nst_gid: %u\nst_rdev: %d\nst_atimespec.tv_sec: %zu\n\
st_mtimespec.tv_sec: %zu\nst_ctimespec.tv_sec: %zu\nst_size: %lld\n\
st_blocks: %lld\nst_blksize: %d\nst_flags: %u\nst_gen: %u\n", buf.st_dev,
buf.st_ino, buf.st_mode, buf.st_nlink, buf.st_uid, buf.st_gid, buf.st_rdev,
buf.st_atimespec.tv_sec, buf.st_mtimespec.tv_sec, buf.st_ctimespec.tv_sec,
buf.st_size, buf.st_blocks, buf.st_blksize, buf.st_flags, buf.st_gen);
	psw = getpwuid(buf.st_uid);
	grp = getgrgid(buf.st_gid);
	ft_printf("%s\t%s\n", psw->pw_name, grp->gr_name);
	ft_printf("%s%s%s", ctime(&buf.st_atimespec.tv_sec),
			ctime(&buf.st_mtimespec.tv_sec),
			ctime(&buf.st_ctimespec.tv_sec));
	ft_printf((S_ISDIR(buf.st_mode)) ? "d" : "-");
	ft_printf((buf.st_mode & S_IRUSR) ? "r" : "-");
	ft_printf((buf.st_mode & S_IWUSR) ? "w" : "-");
	ft_printf((buf.st_mode & S_IXUSR) ? "x" : "-");
	ft_printf((buf.st_mode & S_IRGRP) ? "r" : "-");
	ft_printf((buf.st_mode & S_IWGRP) ? "w" : "-");
	ft_printf((buf.st_mode & S_IXGRP) ? "x" : "-");
	ft_printf((buf.st_mode & S_IROTH) ? "r" : "-");
	ft_printf((buf.st_mode & S_IWOTH) ? "w" : "-");
	ft_printf((buf.st_mode & S_IXOTH) ? "x" : "-");
	ft_printf("\n");
	return (0);
}


int			main(int argc, char **argv)
{
	if (argc != 3)
		return (ft_usage());
	if (ft_list_dir(argv[1]))
		return (2);
	if (ft_inspect_file(argv[2]))
		return (3);
	return (0);
}
