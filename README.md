# Digital Signal Processing: 16-QAM Demodulation & Signal Recovery

## Project Overview

This project explores fundamental concepts in **Digital Signal Processing (DSP)**, **telecommunications**, and **physical layer communications** through a practical implementation of 16-QAM demodulation with signal descrambling. The work demonstrates how wireless signals are decoded and recovered in real communication systems, with direct applications to cybersecurity and network analysis.

### Educational Purpose
This project is a learning exercise in understanding the signal processing pipeline used in modern wireless communications, from raw signal capture to information recovery. It serves as a foundation for understanding physical layer security, wireless threat detection, and secure communications.

---

## Why This Matters: Relevance to Cybersecurity

### Digital Signal Processing (DSP) — Core Academic Field
DSP is fundamental to understanding how modern communication systems work. In cybersecurity, DSP knowledge enables:
- Detection of anomalous signal patterns that indicate attacks
- Analysis of wireless vulnerabilities at the physical layer
- Implementation of secure modulation schemes

### Telecommunications & Modulation Theory — Standard Electrical Engineering
Understanding modulation (how data is encoded onto waves) is critical for:
- Analyzing WiFi and cellular security vulnerabilities
- Detecting signal jamming or spoofing attacks
- Securing wireless protocols against eavesdropping

### Physical Layer Communications — Fundamental Networking Concept
The physical layer is where raw signals travel. Security researchers need to understand it to:
- Identify physical layer attacks (jamming, replay attacks)
- Analyze radio frequency (RF) security
- Reverse engineer proprietary wireless protocols

### Embedded Systems & Low-Level Programming — Systems Engineering
This project demonstrates:
- Efficient bit-level operations in C++
- Real-time signal processing constraints
- Hardware-software interaction on embedded platforms like Raspberry Pi

### Cybersecurity Applications of Signal Processing

#### Wireless Network Security
- Analyze WiFi and cellular signals to detect unauthorized access points
- Understand signal modulation to identify security weaknesses
- Detect signal anomalies that indicate network attacks

#### Software-Defined Radio (SDR) Analysis
- Use SDR tools (like GNU Radio, HackRF) to capture and analyze wireless signals
- Identify rogue transmitters and spectrum abuse
- Perform spectrum monitoring for threat detection

#### Protocol Reverse Engineering
- Understand how signals encode protocol information
- Decode proprietary wireless protocols to identify vulnerabilities
- Analyze signal patterns to reverse engineer communication schemes

#### Network Intrusion Detection
- Detect anomalous signal patterns that indicate attacks
- Monitor spectrum for unauthorized transmissions
- Identify signal characteristics of malware-infected devices

#### Spectrum Analysis and Threat Detection
- Perform frequency domain analysis to detect hidden transmitters
- Identify jamming or denial-of-service attacks on wireless networks
- Monitor compliance with spectrum regulations to detect rogue devices

#### Encryption & Secure Communications
- Understand the physical layer foundation of secure channels
- Implement secure modulation for protected communications
- Analyze signal integrity in encrypted wireless systems

---

## Project Goals

1. **Understand 16-QAM Modulation** — Learn how data is encoded into complex signals
2. **Implement Demodulation** — Convert received signals back to digital bits
3. **Recover Scrambled Data** — Use XOR operations to descramble information
4. **Explore Low-Level Programming** — Work with bit manipulation and signal processing
5. **Apply to Cybersecurity** — Connect physical layer concepts to security challenges

---

## Technical Concepts Explained

### 1. Quadrature Amplitude Modulation (16-QAM)

**What is QAM?**
QAM encodes data by varying both the amplitude and phase of a carrier wave. 16-QAM uses 16 different signal states, each representing 4 bits of information.

**The Constellation Diagram:**
```
        Imaginary (Q)
             |
        ●●●● | ●●●●
        ●●●● | ●●●●  ← Each dot is one of 16 symbols
        ●●●● | ●●●●
  ------|----+----|------ Real (I)
        ●●●● | ●●●●
        ●●●● | ●●●●
        ●●●● | ●●●●
             |
```

Each symbol has real and imaginary components: values from {-3, -1, 1, 3}.

**Why 16-QAM?**
- Efficient use of spectrum (4 bits per symbol)
- Used in WiFi, 4G/5G, and many wireless standards
- Balance between data rate and noise immunity

### 2. Gray Code Mapping

**What is Gray Code?**
Gray code ensures that adjacent symbols differ by only 1 bit. This is critical for noise immunity—if a received signal is slightly corrupted, you get 1 bit error instead of multiple errors.

**Example:**
```
Symbol 14: (real=1, imag=1)   → bits: 1110
Symbol 15: (real=1, imag=3)   → bits: 1100
Difference: Only 1 bit changed (Gray code property!)
```

**Why It Matters:**
- Minimizes burst errors in noisy channels
- Standard in all modern modulation schemes
- Critical for wireless security and reliability

### 3. Demodulation Process

**What is Demodulation?**
Converting received complex signals back to digital bits.

**The Pipeline:**
```
Received Signal (I,Q pairs)
        ↓
Look up in Gray Code Table
        ↓
Extract 4 bits per symbol
        ↓
Concatenate into bit stream
```

**Application to Security:**
- Wireless threat analysis requires demodulating unknown signals
- SDR tools use demodulation to capture proprietary protocols
- Understanding this process helps identify signal vulnerabilities

### 4. Descrambling with XOR

**What is Descrambling?**
Removing a known scrambling pattern to recover original information.

**How XOR Works:**
```
Original bits:    1 1 1 0 1 0
Scramble seq:     1 0 1 1 1 0
                  ⊕ ⊕ ⊕ ⊕ ⊕ ⊕
Scrambled:        0 1 0 1 0 0

To descramble, XOR again:
Scrambled:        0 1 0 1 0 0
Scramble seq:     1 0 1 1 1 0
                  ⊕ ⊕ ⊕ ⊕ ⊕ ⊕
Original:         1 1 1 0 1 0  ✓
```

**Cybersecurity Relevance:**
- XOR is fundamental to cryptography and stream ciphers
- Scrambling protects wireless signals from eavesdropping
- Understanding XOR-based descrambling is essential for protocol analysis

### 5. Bit-Level Programming in C++

**Key Techniques:**
- `bitset<4>` for efficient bit manipulation
- Bit shifting (`<<`, `>>`) for alignment
- Bitwise OR (`|`) and XOR (`^`) operations
- Proper handling of endianness (big-endian vs. little-endian)

**Why It Matters:**
- Embedded systems require efficient bit operations
- Signal processing demands low-level programming
- Security tools often work directly with bit-level data

---

## Implementation Overview

### Architecture
```
┌──────────────────────────────────────┐
│   Binary Signal File (I,Q Samples)   │
└──────────────┬───────────────────────┘
               ↓
┌──────────────────────────────────────┐
│  1. Signal Reading & Parsing         │
│     - Load complex samples            │
│     - Verify data integrity          │
└──────────────┬───────────────────────┘
               ↓
┌──────────────────────────────────────┐
│  2. Demodulation                     │
│     - Gray code lookup               │
│     - Extract 4 bits per symbol      │
│     - Concatenate into bit stream    │
└──────────────┬───────────────────────┘
               ↓
┌──────────────────────────────────────┐
│  3. Descrambling                     │
│     - Apply XOR with key sequence    │
│     - Recover original bit stream    │
└──────────────┬───────────────────────┘
               ↓
┌──────────────────────────────────────┐
│  4. ASCII Conversion                 │
│     - Group 8 bits → 1 character     │
│     - Display decoded message        │
└──────────────────────────────────────┘
```

### Code Quality Standards

- **Clean, Readable Code**: Meaningful variable names, single-responsibility functions
- **Best Practices**: Follows Google C++ Style Guide and C++ Core Guidelines
- **Efficiency**: Optimized for embedded systems with pre-allocation and pass-by-reference
- **RAII Principles**: Proper resource management with automatic file handling

---

## Key Functions

### `readBinaryFile(filename)`
- **Purpose**: Load complex signal samples from binary file
- **Input**: Filename containing I/Q samples as int8_t values
- **Output**: Vector of samples ready for processing
- **Security Note**: Input validation crucial for preventing buffer overflows

### `demodulate(real, imag)`
- **Purpose**: Convert complex symbol to 4 bits using Gray code mapping
- **Input**: Real and imaginary components of a 16-QAM symbol
- **Output**: 4-bit unsigned integer
- **Application**: Core of physical layer signal decoding

### `descramble(scrambled_bits)`
- **Purpose**: Remove scrambling by XORing with known sequence
- **Input**: Scrambled bit stream
- **Output**: Original bit stream
- **Security Relevance**: Demonstrates how known-key cryptography works

### `bitsToASCII(bits)`
- **Purpose**: Convert bit stream to readable ASCII text
- **Input**: Concatenated bit stream
- **Output**: Decoded message string
- **Note**: Error handling for invalid characters

---

## Learning Outcomes

### DSP Fundamentals
✓ Modulation and demodulation concepts
✓ Constellation diagrams and signal mapping
✓ Sampling theory and complex signal representation
✓ Gray coding for noise resilience

### Signal Processing Techniques
✓ Signal conditioning and preprocessing
✓ Bit extraction and manipulation
✓ Frequency and time domain concepts
✓ Real-time processing constraints

### Low-Level Programming
✓ Bit-level operations and bit shifting
✓ Endianness and byte ordering
✓ Memory-efficient data structures
✓ Embedded systems optimization

### Cybersecurity Connections
✓ Physical layer security concepts
✓ Wireless protocol analysis fundamentals
✓ Signal anomaly detection
✓ SDR and spectrum analysis basics

### Software Engineering
✓ Clean code principles
✓ Function design and modularity
✓ Input validation and error handling
✓ Documentation and code maintainability

---

## References & Further Reading

### Academic Resources
- **Digital Signal Processing**: Oppenheim & Schafer (Prentice Hall)
- **Communication Systems**: Haykin & Moher
- **Wireless Communications**: Goldsmith (Cambridge University Press)

### Online Learning
- Wikipedia: [Quadrature Amplitude Modulation](https://en.wikipedia.org/wiki/Quadrature_amplitude_modulation)
- Wikipedia: [Gray Code](https://en.wikipedia.org/wiki/Gray_code)
- Wikipedia: [Demodulation](https://en.wikipedia.org/wiki/Demodulation)

### Cybersecurity & Physical Layer Security
- GNU Radio: [Open-source SDR toolkit](https://www.gnuradio.org/)
- NIST: [Wireless Security Guidelines](https://csrc.nist.gov/)
- IEEE: [Physical Layer Security Research](https://ieeexplore.ieee.org/)

### C++ Best Practices
- [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)
- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)
- [Effective C++](https://www.aristeia.com/books.html) - Scott Meyers

---

## How to Use This Repository

### For Learning DSP
1. Start with qam-theory for concept overview
2. Review gray-coding for Gray code explanation
3. Study qam_demodulator for implementation details
4. Run examples and modify thresholds to see effects

### For Cybersecurity Applications
1. Learn how demodulation applies to SDR analysis
2. Understand signal recovery for protocol reverse engineering
3. Explore how physical layer knowledge prevents attacks
4. Connect to wireless security and threat detection

### For Professional Development
1. Review code structure and naming conventions
2. Study optimization techniques for embedded systems
3. Learn best practices in signal processing implementation
4. Understand how low-level programming supports security

---

## Disclaimer & Educational Use

This project is for **educational purposes only**, designed to teach fundamental concepts in digital signal processing and their application to cybersecurity. All code is original work created as part of learning these concepts.

**Note on Responsibility**: Understanding signal processing and wireless communications should be used responsibly and ethically. Always comply with local regulations when working with radio frequencies and wireless signals.

---

## Author Notes

This project represents my journey into understanding the physical layer of communications systems. Through implementing 16-QAM demodulation, I gained deep insights into:
- How wireless signals actually work at the bit level
- The importance of signal integrity and noise immunity
- How cybersecurity begins at the physical layer
- The elegance of low-level systems programming

These foundational concepts are essential for anyone interested in wireless security, embedded systems, or communications technology.

---

**Last Updated**: November 2025
**Language**: C++
**License**: MIT (Open for educational use)
**Contact**: See GitHub profile for inquiries
