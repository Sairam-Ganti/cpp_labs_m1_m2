# System Overview

The starter model uses a synthetic host-to-device flow:

```text
create descriptor
submit descriptor
notify device
process descriptor
write completion
read completion
print counters
```

## Components

## RegisterMap

A simple offset-based 32-bit register map.

## RingQueue

A bounded circular queue used for submissions and completions.

## SimpleDevice

A synthetic model that accepts descriptors, processes them, and produces completions.

## PerfCounters

A small struct for tracking submitted work, completed work, failures, and bytes processed.

## What this model intentionally omits

- Real device protocols
- Real address translation
- Real driver behavior
- Real timing accuracy
- Vendor-specific behavior
