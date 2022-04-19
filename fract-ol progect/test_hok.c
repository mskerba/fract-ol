#include <mlx.h>
#include "mlx.h"
#include <stdio.h>

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

int	key_hook(int keycode, int x, int y, t_vars *vars)
{
	// (void) keycode;
	(void)vars;
	// (void)x;
	// (void)y;
	// printf("d\n");
	// printf("x = %d,,,,y = %d\n",x,y);
	printf("Hello from key_hook!x = %d, y= %d,%d\n",keycode,x, y);
	return 0;
}
int	main(void)
{
	t_vars	vars;
	// int x = 0;
	// int y = 0;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 640, 480, "Hello world!");
	// mlx_key_hook(vars.win, key_hook, &vars);
	// mlx_mouse_get_pos(vars.win,&x,&y);
	// y = mlx_mouse_hook(vars.win, key_hook, &vars);
	// printf("Hello from key_hook!%d\n",y);
	mlx_hook(vars.win, 4,0L, key_hook, &vars);
	mlx_loop(vars.mlx);
}