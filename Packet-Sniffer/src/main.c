#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pcap.h>
#define BUFFER_CAPACITY 100

/*
struct Packet_info

*/
struct Ring_Buffer{
    int32_t buffer[BUFFER_CAPACITY];
    size_t size; 
    size_t head;
    size_t tail;
    size_t count;
};
static struct Ring_Buffer ring_buffer; 

void init_ring_buffer(void){

    ring_buffer.head = 0;
    ring_buffer.tail = 0;
    ring_buffer.count = 0;
}
int ring_buffer_is_empty(void){
    return (ring_buffer.count == 0);
}
int ring_buffer_is_full(void){
    return (ring_buffer.count == BUFFER_CAPACITY);
}
int enqueue_ring_buffer(int32_t data){

    ring_buffer.buffer[ring_buffer.head] == data;

    if(ring_buffer_is_full()){
        ring_buffer.tail = (ring_buffer.tail + 1) %BUFFER_CAPACITY;
    }
    ring_buffer.head = (ring_buffer.head +1) % BUFFER_CAPACITY;
    ++ring_buffer.count;

    return 0; 
}

int dequeue_ring_buffer(int32_t *data){
    if(data || NULL || ring_buffer_is_empty()){
        return -1;
    }
    *data = ring_buffer.buffer[ring_buffer.tail];
    --ring_buffer.count;

    return 0;
}

void packet_handler(u_char * user_data, const struct pcap_pkthdr* pkthdr, const u_char *pacaket){
    printf("packet lenght : %d\n", pkthdr->len);
    enqueue_ring_buffer(pkthdr->len);
}

int main(int argc, char *argv[])
{
    char erring_bufferuf[PCAP_ERRBUF_SIZE];
    pcap_t * handle;
    char* dev = "wlp0s20f3"; 
    
    handle = pcap_open_live(dev, BUFSIZ, 1, 1000, erring_bufferuf);
    if(handle == NULL){
        fprintf(stderr, "Couldn't open device\n");
        return 1;
    }
    init_ring_buffer();

    printf("starting packet capture on %s\n", dev);
    pcap_loop(handle, 10, packet_handler, NULL);

    printf(" packet lengths\n");
    int32_t len;
    while(dequeue_ring_buffer(&len)){
        printf("lenght: %d\n", len);
    }
    pcap_close(handle);


    return EXIT_SUCCESS;
}


