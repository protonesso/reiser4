/*
  Copyright (c) 2014-2017 Eduard Shishkin

  This file is licensed to you under your choice of the GNU Lesser
  General Public License, version 3 or any later version (LGPLv3 or
  later), or the GNU General Public License, version 2 (GPLv2), in all
  cases as published by the Free Software Foundation.
*/

#ifndef VOLUME_H
#define VOLUME_H

#define METADATA_SUBVOL_ID  (0)

static inline reiser4_subvol *current_meta_subvol(void)
{
	return current_origin(METADATA_SUBVOL_ID);
}

/*
 * Returns true, if meta-data subvolume participates in AID.
 * Otherwise, returns false
 */
static inline int meta_subvol_is_in_aid(void)
{
	return current_meta_subvol()->data_room != 0;
}

/*
 * Returns number of subvolumes participating in AID
 */
static u64 num_aid_subvols(reiser4_volume *vol)
{
	if (meta_subvol_is_in_aid())
		return vol->num_origins;
	else
		return vol->num_origins - 1;
}

/*
 * Returns matrix of subvolumes participating in AID
 */
static inline reiser4_subvol ***current_aid_subvols(void)
{
	if (meta_subvol_is_in_aid())
		return current_subvols();
	else
		return current_subvols() + 1;
}

extern void deactivate_subvol(struct super_block *super, reiser4_subvol *subv);

/*
  Local variables:
  c-indentation-style: "K&R"
  mode-name: "LC"
  c-basic-offset: 8
  tab-width: 8
  fill-column: 80
  scroll-step: 1
  End:
*/

#endif /* VOLUME_H */