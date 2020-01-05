#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
typedef struct s_game
{
    void    *mlx;
    void    *win;
}               t_game;

int keypress(int keycode, t_game *game)
{
    char l;
    char *c;
    int wr;
   
    c = malloc(sizeof(char) * 2);
    l = keycode + '0';
    *c = l;
    *(c + 1) = 0;
    mlx_string_put(game->mlx, game->win, 20, 20, 0x00FFFFFF, c);
    wr = write(1, &l, 1);
    wr++;
    free(c);
    return (0);
}


int	main(void)
{
	int	i;
	t_game  *game;

    game = malloc(sizeof(t_game*));
	i = 0;
	while (i < 10)
		i++;
    game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, 1280, 720, "test");
    mlx_string_put(game->mlx, game->win, 10, 10, 0x00FFFFFF, "hola mundo");
    mlx_hook(game->win, 3, 0, &keypress, (void*)game);
	mlx_loop(game->mlx);
	return (0);
}
