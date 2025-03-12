#include "cub3d.h"

// move ot header file
# ifndef O_DIRECTORY
#  define O_DIRECTORY 00200000
# endif


// // need refactoring less lines of code
// int ft_file_and_dir_checker(char *arg, bool cub_file)
// {
//     int fd;
//     size_t len;
//     // bool is_dir = false;

//     // Check if the argument is a directory
//     fd = open(arg, O_DIRECTORY);
//     if (fd >= 0)
//     {
//         close(fd);
//         return ft_error_msg(arg, ERR_FILE_IS_DIR, STATUS_FAIL);
//     }

//     // Check if the file can be opened
//     fd = open(arg, O_RDONLY);
//     if (fd == -1)
//         return ft_error_msg(arg, strerror(errno), STATUS_FAIL);
//     close(fd);

//     // Check file extension xpm and cup
//     len = ft_strlen(arg);
//     if (cub_file)
//     {
//         if (len < 4 || arg[len - 4] != '.' || arg[len - 3] != 'c' || arg[len - 2] != 'u' || arg[len - 1] != 'b')
//             return ft_error_msg(arg, ERR_FILE_NOT_CUB, STATUS_FAIL);
//     }
//     else
//     {
//         if (len < 4 || arg[len - 4] != '.' || arg[len - 3] != 'x' || arg[len - 2] != 'p' || arg[len - 1] != 'm')
//             return ft_error_msg(arg, ERR_FILE_NOT_XPM, STATUS_FAIL);
//     }

//     return STATUS_OK;
// }

bool	ft_comfirm_dir(char *arg)
{
	int		fd;
	bool	ret;

	ret = false;
	fd = open(arg, O_DIRECTORY);
	if (fd >= 0)
	{
		close (fd);
		ret = true;
	}
	return (ret);
}

bool	ft_confirm_cub_file(char *arg)
{
	size_t	len;

	len = ft_strlen(arg);
	if ((arg[len - 3] != 'c' || arg[len - 2] != 'u'
			|| arg[len - 1] != 'b'
			|| arg[len - 4] != '.'))
		return (false);
	return (true);
}

static bool	ft_comfirm_xpm_file(char *arg)
{
	size_t	len;

	len = ft_strlen(arg);
	if ((arg[len - 3] != 'x' || arg[len - 2] != 'p'
			|| arg[len - 1] != 'm'
			|| arg[len - 4] != '.'))
		return (false);
	return (true);
}

int	ft_file_and_dir_checker(char *arg, bool cub_file)
{
	int	fd;

	if (ft_comfirm_dir(arg))
		return (ft_error_msg(arg, ERR_FILE_IS_DIR, STATUS_FAIL));
	fd = open(arg, O_RDONLY);
	if (fd == -1)
		return (ft_error_msg(arg, strerror(errno), STATUS_FAIL));
	close(fd);
	if (cub_file && !ft_confirm_cub_file(arg))
		return (ft_error_msg(arg, ERR_FILE_NOT_CUB, STATUS_FAIL));
	if (!cub_file && !ft_comfirm_xpm_file(arg))
		return (ft_error_msg(arg, ERR_FILE_NOT_XPM, STATUS_FAIL));
	return (STATUS_OK);
}
