#include <cstdio>     // For C-style I/O
#include <cstdlib>    // For std::exit etc.
#include <ctime>      // For time and data
#include <pcap.h>     // For functions that let program Npcap


int main2() {
  
  pcap_if_t *alldevs;
  pcap_if_t *d;
  int i=0;
  char errbuf[PCAP_ERRBUF_SIZE]{};
  
  /* Retrieve the device list from the local machine */
  if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING,
    NULL /* auth is not needed */,
    &alldevs, errbuf) == -1)
  {
    fprintf(stderr,
      "Error in pcap_findalldevs_ex: %s\n",
      errbuf);
    exit(1);
  }
  
  /* Print the list */
  for(d= alldevs; d != NULL; d= d->next)
  {
    printf("%d. %s", ++i, d->name);
    if (d->description)
      printf(" (%s)\n", d->description);
    else
      printf(" (No description available)\n");
  }

  if (i == 0)
  {
    printf("\nNo interfaces found! Make sure Npcap is installed.\n");
    return 1;
  }

  // Open a network interface i.e. get device to capture
  int inum{};
  printf("Enter the interface number (1-%d):",i);
  scanf_s("%d", &inum);
  if(inum < 1 || inum > i)
  {
    printf("\nInterface number out of range.\n");
    /* Free the device list */
    pcap_freealldevs(alldevs);
    return -1;
  }
  /* Jump to the selected adapter */
  for(d=alldevs, i=0; i< inum-1 ;d=d->next, i++);

  /* Open the device */
  // Ptr to open packet-capture session
  pcap_t *adhandle;
  if ( (adhandle= pcap_open(d->name, // name of the device
          65536, // portion of the packet to capture
                 // 65536 guarantees that the whole packet will
                 // be captured on all the link layers
          PCAP_OPENFLAG_PROMISCUOUS, // promiscuous mode
          1000, // read timeout
          NULL, // authentication on the remote machine
          errbuf // error buffer
          ) ) == NULL)
  {
    fprintf(stderr,
      "\nUnable to open the adapter. %s is not supported by Npcap\n",
      d->name);
    /* Free the device list */
    pcap_freealldevs(alldevs);
    return -1;
  }
  printf("\nlistening on %s...\n", d->description);

  /* At this point, we don't need any more the device list. Free it */
  pcap_freealldevs(alldevs);
  
  // Capture Packets
  /* Retrieve the packets */
  pcap_pkthdr* header = nullptr;
  // Ptr to packet data
  // Npcap manages lifetime -> no dont deallocate yourself; if need data pointed at, copy it into a different variable
  const u_char* pkt_data = nullptr;
  struct tm ltime;
  char timestr[16];
  time_t local_tv_sec;
  int res;
  /*
  * pcpap_next_ex() returns       ->     while() loop behaviour
  *     1: packet captured    ->     process packet (print details)
  *     0: timeout (no packet avilable in specified time)   ->     keep listening
  *     -1: capture error   ->     break out of loop and report error
  *     -2: end of file for an offline capture    ->    break out of loop  
  * NOTE: currently have to break out of this manually e.g. with ctrl+c: change later
  */
  while((res = pcap_next_ex( adhandle, &header, &pkt_data)) >= 0){
    // Timeout
    if(res == 0)
    {
      continue;
    }

    /* convert the timestamp to readable format */
    local_tv_sec = header->ts.tv_sec;
    localtime_s(&ltime, &local_tv_sec);
    strftime(timestr, sizeof timestr, "%H:%M:%S", &ltime);

    printf("%s,%.6ld len:%d\n", timestr, header->ts.tv_usec, header->len);
  }

  // Capture error: print error message, close handle, return -1
  if(res == -1){
    printf("Error reading the packets: %s\n", pcap_geterr(adhandle));
    pcap_close(adhandle);
    return -1;
  }

  pcap_close(adhandle);
  return 0;
  
}
