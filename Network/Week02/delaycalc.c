#include <stdio.h>
#include <stdlib.h>

float per_hop_delay(float proc_delay, float queue_delay, float link_distance, float propagation_speed, float pkt_len, float transmission_rate) {
    float result;
    float propagation_delay= link_distance / propagation_speed;
    float transmission_delay= pkt_len / transmission_rate;
    result= proc_delay + queue_delay + propagation_delay + transmission_delay;
    return result;
}

int main(){
    float proc_delay;
    float queue_delay;
    float link_distance;
    float propagation_speed;
    float pkt_len;
    float transmission_rate;
    printf("Processing delay (ms): ");
    scanf("%f", &proc_delay);
    printf("Queue delay (ms): ");
    scanf("%f", &queue_delay);
    printf("Link distance (m): ");
    scanf("%f", &link_distance);
    printf("Propagation speed (m/ms): ");
    scanf("%f", &propagation_speed);
    printf("Packet length (bit): ");
    scanf("%f", &pkt_len);
    printf("Transmission rate (bit/ms): ");
    scanf("%f", &transmission_rate);
    printf("Delay per hop: %f ms\n", per_hop_delay(proc_delay, queue_delay, link_distance, propagation_speed, pkt_len, transmission_rate));
}
