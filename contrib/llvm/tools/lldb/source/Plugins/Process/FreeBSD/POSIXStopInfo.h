//===-- POSIXStopInfo.h -----------------------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef liblldb_POSIXStopInfo_H_
#define liblldb_POSIXStopInfo_H_

// C Includes
// C++ Includes
// Other libraries and framework includes
// Project includes
#include "lldb/Target/StopInfo.h"

#include "CrashReason.h"
#include "POSIXThread.h"

#include <string>

//===----------------------------------------------------------------------===//
/// @class POSIXStopInfo
/// @brief Simple base class for all POSIX-specific StopInfo objects.
///
class POSIXStopInfo
    : public lldb_private::StopInfo
{
public:
    POSIXStopInfo(lldb_private::Thread &thread, uint32_t status)
        : StopInfo(thread, status)
        { }
};

//===----------------------------------------------------------------------===//
/// @class POSIXLimboStopInfo
/// @brief Represents the stop state of a process ready to exit.
///
class POSIXLimboStopInfo
    : public POSIXStopInfo
{
public:
    POSIXLimboStopInfo(POSIXThread &thread)
        : POSIXStopInfo(thread, 0)
        { }

    ~POSIXLimboStopInfo();

    lldb::StopReason
    GetStopReason() const;

    const char *
    GetDescription();

    bool
    ShouldStop(lldb_private::Event *event_ptr);

    bool
    ShouldNotify(lldb_private::Event *event_ptr);
};


//===----------------------------------------------------------------------===//
/// @class POSIXCrashStopInfo
/// @brief Represents the stop state of process that is ready to crash.
///
class POSIXCrashStopInfo
    : public POSIXStopInfo
{
public:
    POSIXCrashStopInfo(POSIXThread &thread, uint32_t status,
                       CrashReason reason,
                       lldb::addr_t fault_addr);
    ~POSIXCrashStopInfo();

    lldb::StopReason
    GetStopReason() const;
};

//===----------------------------------------------------------------------===//
/// @class POSIXNewThreadStopInfo
/// @brief Represents the stop state of process when a new thread is spawned.
///

class POSIXNewThreadStopInfo
    : public POSIXStopInfo
{
public:
    POSIXNewThreadStopInfo (POSIXThread &thread)
        : POSIXStopInfo (thread, 0)
        { }

    ~POSIXNewThreadStopInfo();

    lldb::StopReason
    GetStopReason() const;

    const char *
    GetDescription();

    bool
    ShouldStop(lldb_private::Event *event_ptr);

    bool
    ShouldNotify(lldb_private::Event *event_ptr);
};

#endif
