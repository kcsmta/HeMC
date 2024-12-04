#define PROFILE

#include "openfhe.h"
#include "utils.h"

using namespace lbcrypto;

int main() {
    std::vector<double> range_values = {-1, 1};
    uint32_t range_size = range_values.size();
    // Step 1: Setup CryptoContext
    uint32_t multDepth = range_size+1;

    uint32_t scaleModSize = 50;

    // The number of neurons
    uint32_t batchSize = 8;

    CCParams<CryptoContextCKKSRNS> parameters;
    parameters.SetMultiplicativeDepth(multDepth);
    parameters.SetScalingModSize(scaleModSize);
    parameters.SetBatchSize(batchSize);

    CryptoContext<DCRTPoly> cc = GenCryptoContext(parameters);

    // Enable the features that you wish to use
    cc->Enable(PKE);
    cc->Enable(KEYSWITCH);
    cc->Enable(LEVELEDSHE);
    std::cout << "CKKS scheme is using ring dimension " << cc->GetRingDimension() << std::endl << std::endl;

    // Step 2: Key Generation
    // B1) Generate encryption keys.
    auto keys = cc->KeyGen();

    // B2) Generate the digit size (need for multiplication)
    cc->EvalMultKeyGen(keys.secretKey);

    // Step 3: Encoding and encryption of inputs
    // Inputs
    std::vector<double> x = {0, 1, 1, 5, -1, -8, 1, -1};

    // Encoding as plaintexts
    Plaintext ptxt_x = cc->MakeCKKSPackedPlaintext(x);

    std::cout << "Input x: " << ptxt_x << std::endl;

    // Encrypt the encoded vectors
    auto ctxt_x = cc->Encrypt(keys.publicKey, ptxt_x);

    // Phase 1 - Server
    std::vector<double> c1 = generateRandomVector(batchSize, -10000, 10000);
    std::vector<double> c2 = generateRandomVector(batchSize, -10000, 10000);

    Plaintext ptxt_c1 = cc->MakeCKKSPackedPlaintext(c1);
    Plaintext ptxt_c2 = cc->MakeCKKSPackedPlaintext(c2);

    Ciphertext<DCRTPoly> temp1;
    for (uint32_t i = 0; i<range_size; i++){
        std::vector<double> constantVector = generateConstantVector(batchSize, range_values[i]);
        Plaintext ptxt_constantVector = cc->MakeCKKSPackedPlaintext(constantVector);
        auto temp2 = cc->EvalSub(ctxt_x, ptxt_constantVector);
        if(i==0){
            temp1 = temp2;
        }
        else{
            temp1 =  cc->EvalMult(temp1, temp2);
        }
    }

    auto temp3 = cc->EvalMult(temp1, ptxt_c1);
    auto ctxt_t = cc->EvalAdd(temp3, ptxt_c2);

    // Phase 2 - Client
    Plaintext ptxt_t_prime;
    cc->Decrypt(keys.secretKey, ctxt_t, &ptxt_t_prime);
    ptxt_t_prime->SetLength(batchSize);
    std::cout << ptxt_t_prime << std::endl;
    auto t_prime = ptxt_t_prime->GetRealPackedValue();

    // Phase 3: Server
    printVector(t_prime);
    printVector(c2);

    return 0;
}