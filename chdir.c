# include <unistd.h>
# include <stdio.h>
# include <linux/limits.h>
# include <string.h>
# include <errno.h>

int	main(int ac, char **av)
{

	char path[PATH_MAX + 1];

	(void)ac;

	getcwd(path, PATH_MAX);
	printf("current pwd : %s\n", path);

	if (chdir(av[1]) == -1)
	{
		printf("%s\n", strerror(errno));
		return (1);
	}
	getcwd(path, PATH_MAX);
	return (0);
}