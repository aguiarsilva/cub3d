#include "cub3d.h"

static void init_ray(t_game *game, t_ray *ray, int x)
{
    // Calculate ray position and direction
    ray->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
    ray->ray_dir_x = game->player.dir_x + game->player.plane_x * ray->camera_x;
    ray->ray_dir_y = game->player.dir_y + game->player.plane_y * ray->camera_x;
    
    // Set initial map position
    ray->map_x = (int)game->player.x_pos;
    ray->map_y = (int)game->player.y_pos;
    
    // Calculate delta distances
    ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
    ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

static void calculate_step_and_side_dist(t_game *game, t_ray *ray)
{
    // Calculate step and initial side distances
    if (ray->ray_dir_x < 0)
    {
        ray->step_x = -1;
        ray->side_dist_x = (game->player.x_pos - ray->map_x) * ray->delta_dist_x;
    }
    else
    {
        ray->step_x = 1;
        ray->side_dist_x = (ray->map_x + 1.0 - game->player.x_pos) * ray->delta_dist_x;
    }
    if (ray->ray_dir_y < 0)
    {
        ray->step_y = -1;
        ray->side_dist_y = (game->player.y_pos - ray->map_y) * ray->delta_dist_y;
    }
    else
    {
        ray->step_y = 1;
        ray->side_dist_y = (ray->map_y + 1.0 - game->player.y_pos) * ray->delta_dist_y;
    }
}

static void perform_dda(t_game *game, t_ray *ray)
{
    int hit;

    hit = 0;
    while (hit == 0)
    {
        // Jump to next map square
        if (ray->side_dist_x < ray->side_dist_y)
        {
            ray->side_dist_x += ray->delta_dist_x;
            ray->map_x += ray->step_x;
            ray->side = 0;
        }
        else
        {
            ray->side_dist_y += ray->delta_dist_y;
            ray->map_y += ray->step_y;
            ray->side = 1;
        }
        // Check if ray has hit a wall
        if (game->map[ray->map_y][ray->map_x] == '1')
            hit = 1;
    }
}

static void calculate_wall_distance(t_ray *ray)
{
    // Calculate distance projected on camera direction
    if (ray->side == 0)
        ray->wall_dist = (ray->side_dist_x - ray->delta_dist_x);
    else
        ray->wall_dist = (ray->side_dist_y - ray->delta_dist_y);
        
    // Calculate height of line to draw on screen
    ray->line_height = (int)(SCREEN_HEIGHT / ray->wall_dist);
    
    // Calculate lowest and highest pixel to fill in current stripe
    ray->draw_start = -ray->line_height / 2 + SCREEN_HEIGHT / 2;
    if (ray->draw_start < 0)
        ray->draw_start = 0;
    ray->draw_end = ray->line_height / 2 + SCREEN_HEIGHT / 2;
    if (ray->draw_end >= SCREEN_HEIGHT)
        ray->draw_end = SCREEN_HEIGHT - 1;
}

static void draw_wall_stripe(t_game *game, t_ray *ray, int x)
{
    int y;
    int color;

    // Choose wall color based on direction (temporary until textures are implemented)
    if (ray->side == 0)
        color = (ray->step_x > 0) ? 0xFF0000 : 0xCC0000;  // Red shades for vertical walls
    else
        color = (ray->step_y > 0) ? 0x00FF00 : 0x00CC00;  // Green shades for horizontal walls

    // Draw the pixels of the stripe
    y = ray->draw_start;
    while (y <= ray->draw_end)
    {
        mlx_pixel_put(game->mlx, game->win, x, y, color);
        y++;
    }
}

void raycaster(t_game *game)
{
    int x;
    t_ray ray;

    x = 0;
    while (x < SCREEN_WIDTH)
    {
        // Initialize ray
        init_ray(game, &ray, x);
        
        // Calculate step and initial side distance
        calculate_step_and_side_dist(game, &ray);
        
        // Perform DDA algorithm
        perform_dda(game, &ray);
        
        // Calculate wall distance and drawing dimensions
        calculate_wall_distance(&ray);
        
        // Draw the wall stripe
        draw_wall_stripe(game, &ray, x);
        
        x++;
    }
}