/* based on the library by Roy Krikke: https://os.mbed.com/users/roykrikke/code/BD_SD_DISCO_F746NG/ */

#ifndef BD_SD_DISCO_F746_H
#define BD_SD_DISCO_F746_H

#include "mbed.h"
#include "BlockDevice.h"
#include "platform/PlatformMutex.h"
#include "stm32746g_discovery_sd.h"

class SD_F746 : public BlockDevice
{
public:

    /** Lifetime of the memory block device
     *
     * Only a block size of 512 bytes is supported
     *
     */
    SD_F746();
    virtual ~SD_F746();

    /** Initialize a block device
     *
     *  @return         0 on success or a negative error code on failure
     */
    virtual int init();

    /** Check if SD card is present in the slot
     *
     * @ return         true if inserted, false otherwise
     */
    virtual int isDetected();

    /** Deinitialize a block device
     *
     *  @return         0 on success or a negative error code on failure
     */
    virtual int deinit();

    /** Read blocks from a block device
     *
     *  @param buffer   Buffer to read blocks into
     *  @param addr     Address of block to begin reading from
     *  @param size     Size to read in bytes, must be a multiple of read block size
     *  @return         0 on success, negative error code on failure
     */
    virtual int read(void *buffer, bd_addr_t addr, bd_size_t size);

    /** Program blocks to a block device
     *
     *  The blocks must have been erased prior to being programmed
     *
     *  @param buffer   Buffer of data to write to blocks
     *  @param addr     Address of block to begin writing to
     *  @param size     Size to write in bytes, must be a multiple of program block size
     *  @return         0 on success, negative error code on failure
     */
    virtual int program(const void *buffer, bd_addr_t addr, bd_size_t size);

    /** Erase blocks on a block device
     *
     *  The state of an erased block is undefined until it has been programmed
     *
     *  @param addr     Address of block to begin erasing
     *  @param size     Size to erase in bytes, must be a multiple of erase block size
     *  @return         0 on success, negative error code on failure
     */
    virtual int erase(bd_addr_t addr, bd_size_t size);

    /** Get the size of a readable block
     *
     *  @return         Size of a readable block in bytes
     */
    virtual bd_size_t get_read_size() const;

    /** Get the size of a programable block
     *
     *  @return         Size of a programable block in bytes
     */
    virtual bd_size_t get_program_size() const;

    /** Get the size of a eraseable block
     *
     *  @return         Size of a eraseable block in bytes
     */
    virtual bd_size_t get_erase_size() const;

    /** Get the total size of the underlying device
     *
     *  @return         Size of the underlying device in bytes
     */
    virtual bd_size_t size() const;

private:
    uint8_t _card_type;
    bd_size_t _read_size;
    bd_size_t _program_size;
    bd_size_t _erase_size;
    bd_size_t _block_size;
    bd_size_t _capacity_in_blocks;
    BSP_SD_CardInfo _current_card_info;
    uint8_t _sd_state;
    uint32_t _timeout;
    PlatformMutex _mutex;
    bool _is_initialized;

    virtual void
    lock () {
        _mutex.lock();
    }

    virtual void
    unlock() {
        _mutex.unlock ();
    }

};

#endif /* BD_SD_DISCO_F746NI_H */
