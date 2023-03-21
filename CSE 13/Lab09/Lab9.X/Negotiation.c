#include <stdio.h>
#include "BOARD.h"
#include "Negotiation.h"


NegotiationData NegotiationHash(NegotiationData secret){
    secret = (uint64_t)secret;
    uint32_t second_step = (secret * secret);
    NegotiationData hashed_num = second_step % PUBLIC_KEY;
    return hashed_num;
}

int NegotiationVerify(NegotiationData secret, NegotiationData commitment){
    NegotiationData hash_checker;
    hash_checker = NegotiationHash(secret);
    if (hash_checker == commitment){
        return TRUE;
    }
    else{
        return FALSE;
    }
}

NegotiationOutcome NegotiateCoinFlip(NegotiationData A, NegotiationData B){
    NegotiationData var = A ^ B;
    int parity = 0;
    while(var){
        parity = !parity;
        var = var & (var - 1);
    }
    
    if (parity == 1){
        return HEADS;
    }
    else{
        return TAILS;
    }
}

