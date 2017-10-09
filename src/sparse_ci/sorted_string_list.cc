/*
 * @BEGIN LICENSE
 *
 * Forte: an open-source plugin to Psi4 (https://github.com/psi4/psi4)
 * that implements a variety of quantum chemistry methods for strongly
 * correlated electrons.
 *
 * Copyright (c) 2012-2017 by its authors (see COPYING, COPYING.LESSER,
 * AUTHORS).
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

#include "sorted_string_list.h"

namespace psi {
namespace forte {

bool reverse_string_order(const STLBitsetDeterminant& i, const STLBitsetDeterminant& j) {
    int nmo = i.nmo();
    const auto& i_bits = i.bits();
    const auto& j_bits = j.bits();
    for (int p = nmo - 1; p >= 0; --p) {
        if ((i_bits[p] == false) and (j_bits[p] == true))
            return true;
        if ((i_bits[p] == true) and (j_bits[p] == false))
            return false;
    }
    for (int p = 2 * nmo - 1; p >= nmo; --p) {
        if ((i_bits[p] == false) and (j_bits[p] == true))
            return true;
        if ((i_bits[p] == true) and (j_bits[p] == false))
            return false;
    }
    return false;
}

SortedStringList::SortedStringList(const DeterminantHashVec& space,
                                   std::shared_ptr<FCIIntegrals> fci_ints,
                                   SpinType sorted_string_spin) {
    nmo_ = fci_ints->nmo();
    // Copy and sort the determinants
    sorted_dets_ = space.determinants();
    num_dets_ = sorted_dets_.size();

    if (sorted_string_spin == SpinType::AlphaSpin) {
        std::sort(sorted_dets_.begin(), sorted_dets_.end(), reverse_string_order);
    } else {
        std::sort(sorted_dets_.begin(), sorted_dets_.end());
    }

    outfile->Printf("\n\n Sorted determinants (%zu,%s)\n", num_dets_,
                    sorted_string_spin == SpinType::AlphaSpin ? "Alpha" : "Beta");
    //    for (auto d : sorted_dets_) {
    //        outfile->Printf("\n %s", d.str2().c_str());
    //    }

    STLBitsetDeterminant half_bit_mask(nmo_);
    if (sorted_string_spin == SpinType::AlphaSpin) {
        for (int i = 0; i < nmo_; i++)
            half_bit_mask.set_alfa_bit(i, true);
    } else {
        for (int i = 0; i < nmo_; i++)
            half_bit_mask.set_beta_bit(i, true);
    }

    // Find the unique strings and their range
    STLBitsetDeterminant first_string;
    STLBitsetDeterminant last_first_string(sorted_dets_[0].bits() & half_bit_mask.bits());

    first_string_range_[last_first_string] = std::make_pair(0, 0);
    outfile->Printf("\n %6d %s", 0, sorted_dets_[0].str2(nmo_).c_str());
    for (size_t i = 1; i < num_dets_; i++) {
        outfile->Printf("\n %6d %s", i, sorted_dets_[i].str2(nmo_).c_str());
        first_string.set_bits(sorted_dets_[i].bits() & half_bit_mask.bits());
        if (not(first_string == last_first_string)) {
            first_string_range_[last_first_string].second = i;
            first_string_range_[first_string] = std::make_pair(i, 0);
            outfile->Printf(" <- new determinant (%zu -> %zu)",
                            first_string_range_[last_first_string].first,
                            first_string_range_[last_first_string].second);
            last_first_string = first_string;
        }
    }
    first_string_range_[last_first_string].second = num_dets_;
}

const std::vector<STLBitsetDeterminant>& SortedStringList::sorted_dets() { return sorted_dets_; }
const det_hash<std::pair<size_t, size_t>>& SortedStringList::first_string_range() {
    return first_string_range_;
}
}
}
