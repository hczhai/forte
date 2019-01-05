/*
 * @BEGIN LICENSE
 *
 * Forte: an open-source plugin to Psi4 (https://github.com/psi4/psi4)
 * that implements a variety of quantum chemistry methods for strongly
 * correlated electrons.
 *
 * Copyright (c) 2012-2019 by its authors (see COPYING, COPYING.LESSER, AUTHORS).
 *
 * The copyrights for code used from other parties are included in
 * the corresponding files.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see http://www.gnu.org/licenses/.
 *
 * @END LICENSE
 */

#ifndef _reference_h_
#define _reference_h_

#include <ambit/tensor.h>

namespace forte {

class ForteIntegrals;
class MOSpaceInfo;

class Reference {
  public:
    // ==> Class Interface <==

    /// Obtain reference energy
    double get_Eref() { return Eref_; }

    /// Obtain density cumulants
    ambit::Tensor L1a() const { return L1a_; }
    ambit::Tensor L1b() const { return L1b_; }
    ambit::Tensor L2aa() const { return L2aa_; }
    ambit::Tensor L2ab() const { return L2ab_; }
    ambit::Tensor L2bb() const { return L2bb_; }
    ambit::Tensor L3aaa() const { return L3aaa_; }
    ambit::Tensor L3aab() const { return L3aab_; }
    ambit::Tensor L3abb() const { return L3abb_; }
    ambit::Tensor L3bbb() const { return L3bbb_; }

    /// Obtain 2-RDMs
    ambit::Tensor g2aa() const { return g2aa_; }
    ambit::Tensor g2ab() const { return g2ab_; }
    ambit::Tensor g2bb() const { return g2bb_; }
    ambit::Tensor SFg2() const { return SFg2_; }

    /// Obtain 3-RDMs
    ambit::Tensor g3aaa() const { return g3aaa_; }
    ambit::Tensor g3aab() const { return g3aab_; }
    ambit::Tensor g3abb() const { return g3abb_; }
    ambit::Tensor g3bbb() const { return g3bbb_; }

    // => Set functions <=

    /// Energy
    void set_Eref(double value) { Eref_ = value; }

    /// One RDMs or cumulants
    void set_L1a(ambit::Tensor L1a) { L1a_ = L1a; }
    void set_L1b(ambit::Tensor L1b) { L1b_ = L1b; }

    /// Two cumulants
    void set_L2aa(ambit::Tensor L2aa) { L2aa_ = L2aa; }
    void set_L2ab(ambit::Tensor L2ab) { L2ab_ = L2ab; }
    void set_L2bb(ambit::Tensor L2bb) { L2bb_ = L2bb; }

    /// Three cumulants
    void set_L3aaa(ambit::Tensor L3aaa) { L3aaa_ = L3aaa; }
    void set_L3aab(ambit::Tensor L3aab) { L3aab_ = L3aab; }
    void set_L3abb(ambit::Tensor L3abb) { L3abb_ = L3abb; }
    void set_L3bbb(ambit::Tensor L3bbb) { L3bbb_ = L3bbb; }

    /// Two reduced density matrices
    void set_g2aa(ambit::Tensor g2aa) { g2aa_ = g2aa; }
    void set_g2ab(ambit::Tensor g2ab) { g2ab_ = g2ab; }
    void set_g2bb(ambit::Tensor g2bb) { g2bb_ = g2bb; }
    void set_SFg2(ambit::Tensor SFg2) { SFg2_ = SFg2; } // Spin-free 2-RDM

    void set_L1(ambit::Tensor L1a, ambit::Tensor L1b) {
        L1a_ = L1a;
        L1b_ = L1b;
    }

    void set_L2(ambit::Tensor L2aa, ambit::Tensor L2ab, ambit::Tensor L2bb) {
        L2aa_ = L2aa;
        L2ab_ = L2ab;
        L2bb_ = L2bb;
    }

    void set_G2(ambit::Tensor g2aa, ambit::Tensor g2ab, ambit::Tensor g2bb) {
        g2aa_ = g2aa;
        g2ab_ = g2ab;
        g2bb_ = g2bb;
    }

    void set_L3(ambit::Tensor L3aaa, ambit::Tensor L3aab, ambit::Tensor L3abb,
                ambit::Tensor L3bbb) {
        L3aaa_ = L3aaa;
        L3aab_ = L3aab;
        L3abb_ = L3abb;
        L3bbb_ = L3bbb;
    }

    void set_G3(ambit::Tensor g3aaa, ambit::Tensor g3aab, ambit::Tensor g3abb,
                ambit::Tensor g3bbb) {
        g3aaa_ = g3aaa;
        g3aab_ = g3aab;
        g3abb_ = g3abb;
        g3bbb_ = g3bbb;
    }

  protected:
    // ==> Class Data <==

    /// Reference energy (include frozen-core and nuclear repulsion)
    double Eref_ = 0.0;

    /// Density cumulants
    ambit::Tensor L1a_ = ambit::Tensor::build(ambit::CoreTensor, "L1a", {0, 0});
    ambit::Tensor L1b_ = ambit::Tensor::build(ambit::CoreTensor, "L1b", {0, 0});
    ambit::Tensor L2aa_ = ambit::Tensor::build(ambit::CoreTensor, "L2aa", {0, 0, 0, 0});
    ambit::Tensor L2ab_ = ambit::Tensor::build(ambit::CoreTensor, "L2ab", {0, 0, 0, 0});
    ambit::Tensor L2bb_ = ambit::Tensor::build(ambit::CoreTensor, "L2bb", {0, 0, 0, 0});
    ambit::Tensor L3aaa_;
    ambit::Tensor L3aab_;
    ambit::Tensor L3abb_;
    ambit::Tensor L3bbb_;

    /// Reduced density matrices
    ambit::Tensor g2aa_;
    ambit::Tensor g2ab_;
    ambit::Tensor g2bb_;
    ambit::Tensor SFg2_; // Spin-free 2-RDM
    ambit::Tensor g3aaa_;
    ambit::Tensor g3aab_;
    ambit::Tensor g3abb_;
    ambit::Tensor g3bbb_;
};

double compute_Eref_from_reference(const Reference& ref, std::shared_ptr<ForteIntegrals> ints,
                                   std::shared_ptr<MOSpaceInfo> mo_space_info, double Enuc);
} // namespace forte

#endif // _reference_h_
