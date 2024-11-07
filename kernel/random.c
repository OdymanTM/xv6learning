static unsigned long int next = 1;  
int random(void)  
{
    next = next * 1103515245 + 12345;
    return (unsigned int) (next / 65536) % 32768;
}

int rand_ticket(int total_tickets) {
    return (random() % total_tickets) + 1;
}
