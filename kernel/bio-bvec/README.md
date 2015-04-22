A `bio` uses an array of `bio_vec` (`bvec`) structures. The `bi_vnct` field of the structure is the number of bvecs. In order to print the useful data length in each bvec one would use `bio_for_each_segment` and then use the `bv_len` field in the `bio_vec` structure, such as below (also in the source code)

    bio_for_each_segment(bvec, bio, idx) {
            pr_alert("bvec %u uses %u bytes starting from offset %u\n",
                          idx, bvec->bv_len, bvec->bv_offset);
    }

Using `bio_cur_bytes` only shows the useful data length in the first `bvec` of the `bio` (the one pointed by the `bi_idx` in the structure). It shouldn't be used in conjunction with `bio_for_each_segment` as it will not print the data length in each `bvec`.
