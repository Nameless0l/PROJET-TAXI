void update_pos(int value)
{
    if (updates_params->bike_pos.x == updates_params->client_pos.x) // move the two to the client destination
    {
        if (updates_params->bike_pos.x == updates_params->client_dest.x)
        {
            updates_params->client_pos.y = WIDTH * 3;
            updates_params->client_pos.x = HEIGHT * 3;
            glutPostRedisplay();
            return;
        }

        float m = (updates_params->bike_pos.y - updates_params->client_dest.y) / (updates_params->bike_pos.x - updates_params->client_dest.x);
        
        int speed = (updates_params->bike_pos.x > updates_params->client_dest.x) ? -SPEED : SPEED;
        updates_params->bike_pos.y += m * speed;
        updates_params->bike_pos.x += speed;        

        updates_params->client_pos.y += m * speed;
        updates_params->client_pos.x += speed;

        glutPostRedisplay();
        glutTimerFunc(15, update_pos, value);
    }
    else
    {
        float m = (updates_params->bike_pos.y - updates_params->client_pos.y) / (updates_params->bike_pos.x - updates_params->client_pos.x);
        
        int speed = (updates_params->bike_pos.x > updates_params->client_pos.x) ? -SPEED : SPEED;
        updates_params->bike_pos.y += m * speed;
        updates_params->bike_pos.x += speed;

        glutPostRedisplay();
        glutTimerFunc(15, update_pos, value);
    }
    
}