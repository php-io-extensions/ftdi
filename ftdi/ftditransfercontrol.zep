namespace Ftdi;

/**
 * Data Transfer Object for libftdi1 asynchronous transfer control state.
 *
 * Populated by FTDI::ftdiWriteDataSubmit() and FTDI::ftdiReadDataSubmit().
 * All pointer fields are stored as opaque integers.
 */
class FTDITransferControl
{
    /** Opaque pointer to struct ftdi_transfer_control cast to int. */
    public handle = 0;

    /** Transfer completion state from struct ftdi_transfer_control::completed. */
    public completed = 0;

    /** Requested transfer size in bytes. */
    public size = 0;

    /** Current transfer offset in bytes. */
    public offset = 0;

    /** Opaque pointer to parent struct ftdi_context cast to int. */
    public contextHandle = 0;

    /** Opaque pointer to transfer buffer cast to int. */
    public bufHandle = 0;

    /** Return all fields as an associative array. */
    public function toArray() -> array
    {
        return [
            "handle":        this->handle,
            "completed":     this->completed,
            "size":          this->size,
            "offset":        this->offset,
            "contextHandle": this->contextHandle,
            "bufHandle":     this->bufHandle
        ];
    }
}
