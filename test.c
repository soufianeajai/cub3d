#include <mlx.h>
#include <stdio.h>
#include <unistd.h>

// Function to periodically check mouse position and print it
void track_mouse_position(void *mlx, void *win)
{
    int x, y;

    while (1)
    {
        mlx_mouse_get_pos(mlx, win, &x, &y);
        printf("Mouse position: (%d, %d)\n", x, y);
 //       usleep(100000); // Sleep for 100 milliseconds
    }
}

int main(void)
{
    void *mlx;
    void *win;

    // Initialize the MLX connection
    mlx = mlx_init();
    if (!mlx)
        return (1);

    // Create a new window
    win = mlx_new_window(mlx, 800, 600, "Mouse Movement Example");
    if (!win)
        return (1);

    // Track mouse position in a loop
    track_mouse_position(mlx, win);

    // Start the MLX loop
    mlx_loop(mlx);

    return (0);
}

