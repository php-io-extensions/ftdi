namespace Ftdi;

/**
 * Data Transfer Object for libftdi1 library version information.
 *
 * Populated by FTDI::ftdiGetLibraryVersion() which wraps
 * ftdi_get_library_version(). No device handle is required.
 */
class FTDIVersionInfo
{
    /** Major version number. */
    public major = 0;

    /** Minor version number. */
    public minor = 0;

    /** Micro (patch) version number. */
    public micro = 0;

    /** Human-readable version string, e.g. "1.5". */
    public versionStr = "";

    /** Snapshot/build identifier string (empty for release builds). */
    public snapshotStr = "";

    /** Return all fields as an associative array. */
    public function toArray() -> array
    {
        return [
            "major":       this->major,
            "minor":       this->minor,
            "micro":       this->micro,
            "versionStr":  this->versionStr,
            "snapshotStr": this->snapshotStr
        ];
    }
}
