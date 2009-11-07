#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pcap.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>
#include <arpa/inet.h>
#include <time.h>

int main (void)
{
	char errbuf[PCAP_ERRBUF_SIZE];
	char *dev;	/* network device to use */
	pcap_t *pd;	/* pcap descriptor */
	const u_char *packet;
	struct pcap_pkthdr hdr;
	struct ether_header *eptr;
	u_char *ptr;
	int i;

	dev = pcap_lookupdev (errbuf);
	if (dev == NULL) {
		fprintf (stderr, "%s\n", errbuf);
		exit (EXIT_FAILURE);
	}

	printf ("Device is: %s\n", dev);

	/* open device for sniffing */
	pd = pcap_open_live (dev, BUFSIZ, 0, -1, errbuf);
	if (pd == NULL) {
		fprintf (stderr, "%s\n", errbuf);
		exit (EXIT_FAILURE);
	}

	packet = pcap_next (pd, &hdr);
	if (packet == NULL) {
		fprintf (stderr, "no packet\n");
		exit (EXIT_FAILURE);
	}

	printf("Grabbed packet of length %d\n", hdr.len);
	printf("Recieved at ..... %s\n",
			ctime ((const time_t*) &hdr.ts.tv_sec)); 
	printf("Ethernet address length is %d\n",ETHER_HDR_LEN);

	/* let's start with the ether header... */
	eptr = (struct ether_header *) packet;

	/* Do a couple of checks to see what packet type we have..*/
	if (ntohs (eptr->ether_type) == ETHERTYPE_IP) {
		printf("Ethernet type hex:%x dec:%d is an IP packet\n",
		ntohs(eptr->ether_type),
		ntohs(eptr->ether_type));
	} else  if (ntohs (eptr->ether_type) == ETHERTYPE_ARP) {
		printf("Ethernet type hex:%x dec:%d is an ARP packet\n",
		ntohs(eptr->ether_type),
		ntohs(eptr->ether_type));
	} else {
		printf("Ethernet type %x not IP", ntohs(eptr->ether_type));
		exit(EXIT_FAILURE);
	}

	ptr = eptr->ether_dhost;
	i = ETHER_ADDR_LEN;
	printf(" Destination Address:  ");
	do {
		printf("%s%02x",(i == ETHER_ADDR_LEN) ? " " : ":",*ptr++);
	} while (--i>0);
	printf("\n");

	ptr = eptr->ether_shost;
	i = ETHER_ADDR_LEN;
	printf(" Source Address:  ");
	do {
		printf("%s%02x",(i == ETHER_ADDR_LEN) ? " " : ":",*ptr++);
	} while (--i>0);
	printf ("\n");

	return 0;
}
