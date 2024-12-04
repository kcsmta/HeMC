#define PROFILE

#include "openfhe.h"
#include "utils.h"

using namespace lbcrypto;

int main() {
    // Step 1: Setup CryptoContext
    uint32_t multDepth = 2;

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
    std::vector<double> x = generateRandomVector(batchSize, -1, 1);
    std::vector<double> sign_x = generateRandomSign(batchSize);

    std::cout << "x = ";printVector(x);
    std::cout << "sign(x) (fake) = ";printVector(sign_x);

    Plaintext ptxt_x = cc->MakeCKKSPackedPlaintext(x);
    Plaintext ptxt_sign_x = cc->MakeCKKSPackedPlaintext(sign_x);

    // Encrypt the encoded vectors
    auto ctxt_x = cc->Encrypt(keys.publicKey, ptxt_x);
    auto ctxt_sign_x = cc->Encrypt(keys.publicKey, ptxt_sign_x);

    // Phase 1 - Server
    std::vector<double> c3 = generateRandomVector(batchSize, -10, 10);
    std::cout << "c3= ";printVector(c3);

    Plaintext ptxt_c3 = cc->MakeCKKSPackedPlaintext(c3);

    auto temp1 = cc->EvalMult(ctxt_x, ctxt_sign_x);
    auto ctxt_t = cc->EvalMult(temp1, ptxt_c3);

    // Phase 2 - Client 
    Plaintext ptxt_t_prime;
    cc->Decrypt(keys.secretKey, ctxt_t, &ptxt_t_prime);
    ptxt_t_prime->SetLength(batchSize);
    auto t_prime = ptxt_t_prime->GetRealPackedValue();
    std::cout << "t' = ";printVector(t_prime); 
    std::vector<double> b_prime = Sign(t_prime);

    // Phase 3 - Server
    std::vector<double> b = Sign(c3);
    std::cout << "b= ";printVector(b);
    std::cout << "b' = ";printVector(b_prime);

    return 0;
}