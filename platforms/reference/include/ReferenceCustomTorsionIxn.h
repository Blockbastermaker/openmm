/* Portions copyright (c) 2010-2016 Stanford University and Simbios.
 * Contributors: Peter Eastman
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS, CONTRIBUTORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef __ReferenceCustomTorsionIxn_H__
#define __ReferenceCustomTorsionIxn_H__

#include "ReferenceBondIxn.h"
#include "openmm/internal/CompiledExpressionSet.h"

namespace OpenMM {

class ReferenceCustomTorsionIxn : public ReferenceBondIxn {

   private:
      Lepton::CompiledExpression energyExpression;
      Lepton::CompiledExpression forceExpression;
      std::vector<Lepton::CompiledExpression> energyParamDerivExpressions;
      CompiledExpressionSet expressionSet;
      std::vector<int> torsionParamIndex;
      int thetaIndex;
      int numParameters;
      bool usePeriodic;
      Vec3 boxVectors[3];

   public:

      /**---------------------------------------------------------------------------------------

         Constructor

         --------------------------------------------------------------------------------------- */

       ReferenceCustomTorsionIxn(const Lepton::CompiledExpression& energyExpression, const Lepton::CompiledExpression& forceExpression,
                              const std::vector<std::string>& parameterNames, std::map<std::string, double> globalParameters,
                              const std::vector<Lepton::CompiledExpression> energyParamDerivExpressions);

      /**---------------------------------------------------------------------------------------

         Destructor

         --------------------------------------------------------------------------------------- */

       ~ReferenceCustomTorsionIxn();

       /**---------------------------------------------------------------------------------------
      
         Set the force to use periodic boundary conditions.
      
         @param vectors    the vectors defining the periodic box
      
         --------------------------------------------------------------------------------------- */
      
       void setPeriodic(OpenMM::Vec3* vectors);

      /**---------------------------------------------------------------------------------------

         Calculate Custom Torsion Ixn

         @param atomIndices      two bond indices
         @param atomCoordinates  atom coordinates
         @param parameters       parameter values
         @param forces           force array (forces added)
         @param totalEnergy      if not null, the energy will be added to this

         --------------------------------------------------------------------------------------- */

      void calculateBondIxn(int* atomIndices, std::vector<OpenMM::Vec3>& atomCoordinates,
                            double* parameters, std::vector<OpenMM::Vec3>& forces,
                            double* totalEnergy, double* energyParamDerivs);


};

} // namespace OpenMM

#endif // _ReferenceCustomTorsionIxn___
