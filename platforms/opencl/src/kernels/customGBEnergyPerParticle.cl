#define REDUCE_VALUE(NAME, TYPE) \
    TYPE sum = NAME[index]; \
    for (int i = index+bufferSize; i < totalSize; i += bufferSize) \
        sum += NAME[i]; \
    NAME[index] = sum;

/**
 * Reduce the derivatives computed in the N^2 energy kernel, and compute all per-particle energy terms.
 */

__kernel void computePerParticleEnergy(int bufferSize, int numBuffers, __global float* energyBuffer
        PARAMETER_ARGUMENTS) {
    float energy = 0.0f;
    unsigned int index = get_global_id(0);
    while (index < NUM_ATOMS) {
        // Reduce the derivatives

        int totalSize = bufferSize*numBuffers;
        REDUCE_DERIVATIVES

        // Now calculate the per-particle energy terms.

        COMPUTE_ENERGY
        index += get_global_size(0);
    }
    energyBuffer[get_global_id(0)] += energy;
}
