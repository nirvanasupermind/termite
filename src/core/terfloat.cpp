#include <cstdint>
#include <string>
#include <iostream>
#include <algorithm>
#include <utility>
#include <cmath>

#include "tryte.h"
#include "word.h"
#include "tables.h"
#include "terfloat.h"

namespace termite {
//         TerFloat::TerFloat()
//         : significand(Word::ZERO), exponent(Word::ZERO) {
//     }

//         TerFloat::TerFloat(Word significand, Word exponent)
//         : significand(significand), exponent(exponent) {

//         }




//     void TerFloat::normalize() {
//         if (significand == Word::ZERO) {
//             exponent = Word::ZERO;
//         }
//         else if (significand > Word::ZERO) {
//             if (significand < Word::MIN_FLOAT_SIG) {
//                 while (significand < Word::MIN_FLOAT_SIG) {
//                     significand = significand.shl_int8(1);
//                     exponent = exponent - Word::ONE;
//                 }
//             }
//             else if (significand >= Word::MAX_FLOAT_SIG) {
//                 while (significand >= Word::MAX_FLOAT_SIG) {
//                     significand = significand.shr_int8(1);
//                     exponent = exponent + Word::ONE;
//                 }
//             }
//         }
//         else if (significand < Word::ZERO) {
//             if (significand > Word::NEG_MIN_FLOAT_SIG) {
//                 while (significand > Word::NEG_MIN_FLOAT_SIG) {
//                     significand = significand.shl_int8(1);
//                     exponent = exponent - Word::ONE;
//                 }
//             }
//             else if (significand <= Word::NEG_MAX_FLOAT_SIG) {
//                 while (significand <= Word::NEG_MAX_FLOAT_SIG) {
//                     significand = significand.shr_int8(1);
//                     exponent = exponent + Word::ONE;
//                 }
//             }
//         }
// //     }

const TerFloat TerFloat::ZERO = TerFloat::from_double(0.0);
const TerFloat TerFloat::HALF = TerFloat::from_double(0.5);
const TerFloat TerFloat::ONE = TerFloat::from_double(1.0);
const TerFloat TerFloat::THREE_HALVES = TerFloat::from_double(1.5);
const TerFloat TerFloat::PI = TerFloat::from_double(3.14159265358979323846);
const TerFloat TerFloat::TWO_PI = TerFloat::from_double(6.28318530717958647692);
const TerFloat TerFloat::HALF_PI = TerFloat::from_double(1.57079632679489661923);
const TerFloat TerFloat::QUARTER_PI = TerFloat::from_double(0.7853981633974483);
const TerFloat TerFloat::SQRT2_MINUS_1 = TerFloat::from_double(0.4142135623730950);

static int dbg1 = []() {
    std::cerr << "AFTER NORMAL CONSTANTS\n";
    return 0;
}();

const TerFloat TerFloat::NEGATIVE_INFINITY =
    TerFloat(Word::NEG_MIN_FLOAT_SIG, Word::from_int32(21523360));

static int dbg2 = []() {
    std::cerr << "AFTER NEG INF\n";
    return 0;
}();

const TerFloat TerFloat::POSITIVE_INFINITY =
    TerFloat(Word::MIN_FLOAT_SIG, Word::from_int32(21523360));

static int dbg3 = []() {
    std::cerr << "AFTER POS INF\n";
    return 0; 
}();

const TerFloat TerFloat::NAN_ =
    TerFloat(Word::MAX_FLOAT_SIG - Word::ONE,
             Word::from_int32(21523360));

static int dbg4 = []() {
    std::cerr << "AFTER NAN -- ABOUT TO INIT REC TABLE\n";
    return 0;
}();

//     const TerFloat TerFloat::ZERO = TerFloat::from_double(0.0);
//     const TerFloat TerFloat::HALF = TerFloat::from_double(0.5);
//     const TerFloat TerFloat::ONE = TerFloat::from_double(1.0);
//     const TerFloat TerFloat::THREE_HALVES = TerFloat::from_double(1.5);
//     const TerFloat TerFloat::PI = TerFloat::from_double(3.14159265358979323846);
//     const TerFloat TerFloat::TWO_PI = TerFloat::from_double(6.28318530717958647692);
//     const TerFloat TerFloat::HALF_PI = TerFloat::from_double(1.57079632679489661923);
//     const TerFloat TerFloat::QUARTER_PI = TerFloat::from_double(0.7853981633974483);
//     const TerFloat TerFloat::SQRT2_MINUS_1 = TerFloat::from_double(0.4142135623730950);
// const TerFloat TerFloat::NEGATIVE_INFINITY =
//     TerFloat(
//         Word(0x45555555),
//         Word::from_int32(21523360)
//     );

// const TerFloat TerFloat::POSITIVE_INFINITY =
//     TerFloat(
//         Word(0x65555555),
//         Word::from_int32(21523360)
//     );

// const TerFloat TerFloat::NAN_ =
//     TerFloat(
//         Word(0x95555555) - Word::ONE,
//         Word::from_int32(21523360)
//     );
    // const TerFloat TerFloat::NEGATIVE_INFINITY = TerFloat(Word::NEG_MIN_FLOAT_SIG, Word::from_int32(21523360));
    // const TerFloat TerFloat::POSITIVE_INFINITY = TerFloat(Word::MIN_FLOAT_SIG, Word::from_int32(21523360));
    // const TerFloat TerFloat::NAN_ = TerFloat(Word::MAX_FLOAT_SIG - Word::ONE, Word::from_int32(21523360));
    // 1/(1), 1/(82/81), 1/(83/81),..., 1/(241/81), 1/(242/81) (ends right before 1/3
    const Word TerFloat::REC_LOOKUP_TABLE[162] = { Word::from_int32((14348907)),Word::from_int32((14173920)),Word::from_int32((14003150)),Word::from_int32((13836446)),Word::from_int32((13673664)),Word::from_int32((13514668)),Word::from_int32((13359327)),Word::from_int32((13207517)),Word::from_int32((13059118)),Word::from_int32((12914016)),Word::from_int32((12772104)),Word::from_int32((12633277)),Word::from_int32((12497435)),Word::from_int32((12364484)),Word::from_int32((12234331)),Word::from_int32((12106890)),Word::from_int32((11982077)),Word::from_int32((11859811)),Word::from_int32((11740015)),Word::from_int32((11622615)),Word::from_int32((11507539)),Word::from_int32((11394720)),Word::from_int32((11284092)),Word::from_int32((11175591)),Word::from_int32((11069157)),Word::from_int32((10964731)),Word::from_int32((10862257)),Word::from_int32((10761680)),Word::from_int32((10662949)),Word::from_int32((10566013)),Word::from_int32((10470824)),Word::from_int32((10377335)),Word::from_int32((10285500)),Word::from_int32((10195276)),Word::from_int32((10106621)),Word::from_int32((10019495)),Word::from_int32((9933859)),Word::from_int32((9849673)),Word::from_int32((9766903)),Word::from_int32((9685512)),Word::from_int32((9605467)),Word::from_int32((9526733)),Word::from_int32((9449280)),Word::from_int32((9373076)),Word::from_int32((9298092)),Word::from_int32((9224297)),Word::from_int32((9151665)),Word::from_int32((9080168)),Word::from_int32((9009779)),Word::from_int32((8940473)),Word::from_int32((8872225)),Word::from_int32((8805011)),Word::from_int32((8738808)),Word::from_int32((8673593)),Word::from_int32((8609344)),Word::from_int32((8546040)),Word::from_int32((8483660)),Word::from_int32((8422185)),Word::from_int32((8361593)),Word::from_int32((8301868)),Word::from_int32((8242989)),Word::from_int32((8184940)),Word::from_int32((8127703)),Word::from_int32((8071260)),Word::from_int32((8015596)),Word::from_int32((7960695)),Word::from_int32((7906541)),Word::from_int32((7853118)),Word::from_int32((7800413)),Word::from_int32((7748410)),Word::from_int32((7697096)),Word::from_int32((7646457)),Word::from_int32((7596480)),Word::from_int32((7547152)),Word::from_int32((7498461)),Word::from_int32((7450394)),Word::from_int32((7402939)),Word::from_int32((7356085)),Word::from_int32((7309821)),Word::from_int32((7264134)),Word::from_int32((7219015)),Word::from_int32((7174454)),Word::from_int32((7130438)),Word::from_int32((7086960)),Word::from_int32((7044009)),Word::from_int32((7001575)),Word::from_int32((6959650)),Word::from_int32((6918223)),Word::from_int32((6877287)),Word::from_int32((6836832)),Word::from_int32((6796851)),Word::from_int32((6757334)),Word::from_int32((6718274)),Word::from_int32((6679664)),Word::from_int32((6641494)),Word::from_int32((6603758)),Word::from_int32((6566449)),Word::from_int32((6529559)),Word::from_int32((6493081)),Word::from_int32((6457008)),Word::from_int32((6421334)),Word::from_int32((6386052)),Word::from_int32((6351156)),Word::from_int32((6316638)),Word::from_int32((6282494)),Word::from_int32((6248718)),Word::from_int32((6215302)),Word::from_int32((6182242)),Word::from_int32((6149532)),Word::from_int32((6117166)),Word::from_int32((6085139)),Word::from_int32((6053445)),Word::from_int32((6022080)),Word::from_int32((5991038)),Word::from_int32((5960315)),Word::from_int32((5929905)),Word::from_int32((5899804)),Word::from_int32((5870007)),Word::from_int32((5840510)),Word::from_int32((5811307)),Word::from_int32((5782395)),Word::from_int32((5753770)),Word::from_int32((5725426)),Word::from_int32((5697360)),Word::from_int32((5669568)),Word::from_int32((5642046)),Word::from_int32((5614790)),Word::from_int32((5587796)),Word::from_int32((5561060)),Word::from_int32((5534578)),Word::from_int32((5508348)),Word::from_int32((5482365)),Word::from_int32((5456627)),Word::from_int32((5431128)),Word::from_int32((5405867)),Word::from_int32((5380840)),Word::from_int32((5356044)),Word::from_int32((5331475)),Word::from_int32((5307130)),Word::from_int32((5283007)),Word::from_int32((5259102)),Word::from_int32((5235412)),Word::from_int32((5211935)),Word::from_int32((5188667)),Word::from_int32((5165607)),Word::from_int32((5142750)),Word::from_int32((5120095)),Word::from_int32((5097638)),Word::from_int32((5075378)),Word::from_int32((5053311)),Word::from_int32((5031435)),Word::from_int32((5009748)),Word::from_int32((4988247)),Word::from_int32((4966929)),Word::from_int32((4945793)),Word::from_int32((4924837)),Word::from_int32((4904057)),Word::from_int32((4883452)),Word::from_int32((4863019)),Word::from_int32((4842756)),Word::from_int32((4822662)),Word::from_int32((4802733)) };
    const Word TerFloat::RSQRT_LOOKUP_TABLE[162] = {Word::from_int32((14348907)),Word::from_int32((14261145)),Word::from_int32((14174974)),Word::from_int32((14090347)),Word::from_int32((14007217)),Word::from_int32((13925542)),Word::from_int32((13845279)),Word::from_int32((13766388)),Word::from_int32((13688830)),Word::from_int32((13612568)),Word::from_int32((13537567)),Word::from_int32((13463793)),Word::from_int32((13391211)),Word::from_int32((13319791)),Word::from_int32((13249501)),Word::from_int32((13180313)),Word::from_int32((13112197)),Word::from_int32((13045126)),Word::from_int32((12979075)),Word::from_int32((12914016)),Word::from_int32((12849926)),Word::from_int32((12786782)),Word::from_int32((12724558)),Word::from_int32((12663235)),Word::from_int32((12602789)),Word::from_int32((12543201)),Word::from_int32((12484451)),Word::from_int32((12426518)),Word::from_int32((12369384)),Word::from_int32((12313031)),Word::from_int32((12257442)),Word::from_int32((12202598)),Word::from_int32((12148485)),Word::from_int32((12095084)),Word::from_int32((12042382)),Word::from_int32((11990363)),Word::from_int32((11939012)),Word::from_int32((11888316)),Word::from_int32((11838259)),Word::from_int32((11788830)),Word::from_int32((11740015)),Word::from_int32((11691801)),Word::from_int32((11644176)),Word::from_int32((11597129)),Word::from_int32((11550647)),Word::from_int32((11504720)),Word::from_int32((11459336)),Word::from_int32((11414486)),Word::from_int32((11370157)),Word::from_int32((11326342)),Word::from_int32((11283028)),Word::from_int32((11240208)),Word::from_int32((11197872)),Word::from_int32((11156011)),Word::from_int32((11114616)),Word::from_int32((11073678)),Word::from_int32((11033189)),Word::from_int32((10993141)),Word::from_int32((10953526)),Word::from_int32((10914336)),Word::from_int32((10875564)),Word::from_int32((10837202)),Word::from_int32((10799243)),Word::from_int32((10761680)),Word::from_int32((10724507)),Word::from_int32((10687716)),Word::from_int32((10651301)),Word::from_int32((10615256)),Word::from_int32((10579574)),Word::from_int32((10544250)),Word::from_int32((10509277)),Word::from_int32((10474650)),Word::from_int32((10440363)),Word::from_int32((10406411)),Word::from_int32((10372788)),Word::from_int32((10339488)),Word::from_int32((10306507)),Word::from_int32((10273840)),Word::from_int32((10241481)),Word::from_int32((10209426)),Word::from_int32((10177671)),Word::from_int32((10146209)),Word::from_int32((10115038)),Word::from_int32((10084153)),Word::from_int32((10053548)),Word::from_int32((10023221)),Word::from_int32((9993166)),Word::from_int32((9963380)),Word::from_int32((9933859)),Word::from_int32((9904598)),Word::from_int32((9875595)),Word::from_int32((9846845)),Word::from_int32((9818345)),Word::from_int32((9790090)),Word::from_int32((9762079)),Word::from_int32((9734306)),Word::from_int32((9706769)),Word::from_int32((9679464)),Word::from_int32((9652389)),Word::from_int32((9625539)),Word::from_int32((9598913)),Word::from_int32((9572506)),Word::from_int32((9546316)),Word::from_int32((9520339)),Word::from_int32((9494574)),Word::from_int32((9469016)),Word::from_int32((9443664)),Word::from_int32((9418514)),Word::from_int32((9393565)),Word::from_int32((9368812)),Word::from_int32((9344254)),Word::from_int32((9319888)),Word::from_int32((9295712)),Word::from_int32((9271723)),Word::from_int32((9247919)),Word::from_int32((9224297)),Word::from_int32((9200856)),Word::from_int32((9177592)),Word::from_int32((9154503)),Word::from_int32((9131588)),Word::from_int32((9108845)),Word::from_int32((9086270)),Word::from_int32((9063863)),Word::from_int32((9041620)),Word::from_int32((9019540)),Word::from_int32((8997622)),Word::from_int32((8975862)),Word::from_int32((8954259)),Word::from_int32((8932812)),Word::from_int32((8911518)),Word::from_int32((8890375)),Word::from_int32((8869383)),Word::from_int32((8848538)),Word::from_int32((8827840)),Word::from_int32((8807286)),Word::from_int32((8786875)),Word::from_int32((8766605)),Word::from_int32((8746475)),Word::from_int32((8726484)),Word::from_int32((8706628)),Word::from_int32((8686907)),Word::from_int32((8667320)),Word::from_int32((8647865)),Word::from_int32((8628540)),Word::from_int32((8609344)),Word::from_int32((8590276)),Word::from_int32((8571334)),Word::from_int32((8552516)),Word::from_int32((8533822)),Word::from_int32((8515250)),Word::from_int32((8496799)),Word::from_int32((8478467)),Word::from_int32((8460253)),Word::from_int32((8442157)),Word::from_int32((8424175)),Word::from_int32((8406309)),Word::from_int32((8388555)),Word::from_int32((8370913)),Word::from_int32((8353383)),Word::from_int32((8335962)),Word::from_int32((8318649)),Word::from_int32((8301444))};
    TerFloat::TerFloat()
        : significand(Word::ZERO), exponent(Word::ZERO) {
    }

    TerFloat::TerFloat(Word significand, Word exponent)
        : significand(significand), exponent(exponent) {
        normalize();
    }

    TerFloat TerFloat::from_double(double n) {
        // std::cout << "STARTED" << '\n';
        // return TerFloat();
        if (n < 0.0) {
            return -TerFloat::from_double(-n);
        }
        if (n == 0.0) return TerFloat(Word::ZERO, Word::ZERO);

        double log3n = std::log(n) / std::log(3);
        double exponent = std::floor(log3n);
        double significand = std::pow(3, (log3n - exponent) + 14);
        return TerFloat(Word::from_int32((int32_t)(std::round(significand))), Word::from_int32((int32_t)(exponent)));
    }

    TerFloat TerFloat::operator+(const TerFloat& other) const {
        if (is_nan() || other.is_nan()) {
            return TerFloat::NAN_;
        }
        else if (*this == TerFloat::POSITIVE_INFINITY) {
            if (other == TerFloat::NEGATIVE_INFINITY) {
                return TerFloat::NAN_;
            }
            else {
                return TerFloat::POSITIVE_INFINITY;
            }
        }
        else if (*this == TerFloat::NEGATIVE_INFINITY) {
            if (other == TerFloat::POSITIVE_INFINITY) {
                return TerFloat::NAN_;
            }
            else {
                return TerFloat::NEGATIVE_INFINITY;
            }
        }
        TerFloat x = *this;
        TerFloat y = other;
        if (exponent < other.exponent) {
            std::swap(x, y);
        }
        Word sum = x.significand + y.significand.shr_int8(x.exponent.to_int32() - y.exponent.to_int32());
        Word shr1_sum = x.significand.shr_int8(1) + y.significand.shr_int8(1 + (x.exponent.to_int32() - y.exponent.to_int32()));
        if (shr1_sum > Word::MIN_FLOAT_SIG || shr1_sum < Word::NEG_MIN_FLOAT_SIG) {
            return TerFloat(shr1_sum, x.exponent + Word::ONE);
        }
        else {
            return TerFloat(x.significand + y.significand.shr_int8(x.exponent.to_int32() - y.exponent.to_int32()), x.exponent);
        }
    }

    TerFloat TerFloat::operator-(const TerFloat& other) const {
        return *this + -other;
    }

    // TerFloat TerFloat::operator*(const TerFloat& other) const {
    //     // TEMPORARY
    //     int64_t p =
    //         (int64_t)significand.to_int32() *
    //         (int64_t)other.significand.to_int32();

    //     int64_t q = p / 4782969LL; // 3^14
    //     Word e = exponent + other.exponent;

    //     while (q >= 14348907LL || q <= -14348907LL) {
    //         q /= 3;
    //         e = e + Word::ONE;
    //     }

    //     while (q > 0 && q < 4782969LL) {
    //         q *= 3;
    //         e = e - Word::ONE;
    //     }

    //     while (q < 0 && q > -4782969LL) {
    //         q *= 3;
    //         e = e - Word::ONE;
    //     }

    //     return TerFloat(Word::from_int32((int32_t)q), e);
    // }

    TerFloat TerFloat::operator*(const TerFloat& other) const {
        if (is_nan() || other.is_nan()) return TerFloat::NAN_;

        if (*this == TerFloat::ZERO || other == TerFloat::ZERO) {
            return TerFloat::ZERO;
        }

        if (is_inf() || other.is_inf()) {
            bool neg = (significand < Word::ZERO) ^ (other.significand < Word::ZERO);
            return neg ? TerFloat::NEGATIVE_INFINITY : TerFloat::POSITIVE_INFINITY;
        }

        std::pair<Word, Word> mul32_res = significand.mul32(other.significand);

        // std::cout << "DBG99" << (significand.to_int32()) << '\n';
        // std::cout << "DBG100 " << mul32_res.first.to_int32() << ' '  << mul32_res.second.to_int32() << '\n';
        Word result_significand = mul32_res.second.shl_int8(2) + mul32_res.first.shr_int8(14);
        return TerFloat(result_significand, exponent + other.exponent);
    }

    // TerFloat TerFloat::operator*(const TerFloat& other) const {
    //     if (is_nan() || other.is_nan()) {
    //         return TerFloat::NAN_;
    //     }
    //     else if (*this == TerFloat::POSITIVE_INFINITY) {
    //         if (other.significand < Word::ZERO) {
    //             return TerFloat::NEGATIVE_INFINITY;
    //         }
    //         else {
    //             return TerFloat::POSITIVE_INFINITY;
    //         }
    //     }
    //     else if (*this == TerFloat::NEGATIVE_INFINITY) {
    //         if (other.significand < Word::ZERO) {
    //             return TerFloat::POSITIVE_INFINITY;
    //         }
    //         else {
    //             return TerFloat::NEGATIVE_INFINITY;
    //         }
    //     }
    //     Word result_sig = significand.mul32(other.significand).second;
    //     return TerFloat(result_sig, exponent + other.exponent + Word::TWO);
    // }


    void TerFloat::normalize() {
        if (significand == Word::ZERO) {
            exponent = Word::ZERO;
        }
        else if (significand > Word::ZERO) {
            if (significand < Word::MIN_FLOAT_SIG) {
                while (significand < Word::MIN_FLOAT_SIG) {
                    significand = significand.shl_int8(1);
                    exponent = exponent - Word::ONE;
                }
            }
            else if (significand >= Word::MAX_FLOAT_SIG) {
                while (significand >= Word::MAX_FLOAT_SIG) {
                    significand = significand.shr_int8(1);
                    exponent = exponent + Word::ONE;
                }
            }
        }
        else if (significand < Word::ZERO) {
            if (significand > Word::NEG_MIN_FLOAT_SIG) {
                while (significand > Word::NEG_MIN_FLOAT_SIG) {
                    significand = significand.shl_int8(1);
                    exponent = exponent - Word::ONE;
                }
            }
            else if (significand <= Word::NEG_MAX_FLOAT_SIG) {
                while (significand <= Word::NEG_MAX_FLOAT_SIG) {
                    significand = significand.shr_int8(1);
                    exponent = exponent + Word::ONE;
                }
            }
        }
    }


    TerFloat TerFloat::rec() const {
        if (significand == Word::ZERO) {
            return TerFloat::POSITIVE_INFINITY;
        }

        TerFloat m(significand, Word::ZERO);

        TerFloat x(REC_LOOKUP_TABLE[(significand.shr_int8(10)).to_int32() - 81], Word::from_int32(-1));
        // 3 iterations
        for (int i = 0; i < 3; i++) {
            x = x * (TerFloat::from_double(2.0) - (m * x));

        }
        // Need to rescale at the end because this has exponent 0
        return  TerFloat(x.significand, x.exponent - exponent);

    }

    TerFloat TerFloat::operator/(const TerFloat& other) const {
        if (is_nan() || other.is_nan()) {
            return TerFloat::NAN_;
        }

        if (other.significand == Word::ZERO) {
            if (significand == Word::ZERO) {
                return TerFloat::NAN_;
            }
            else {
                return TerFloat::POSITIVE_INFINITY;
            }
        }

        if (significand == Word::ZERO) {
            return TerFloat::ZERO;
        }

        return operator*(other.rec());
    }


    TerFloat TerFloat::operator%(const TerFloat& other) const {
        return TerFloat::from_double(std::fmod(to_double(), other.to_double()));
        // return operator-(operator/(other).floor()*other);
    }

        TerFloat TerFloat::rsqrt() const {
        if (significand < Word::ZERO) {
            return TerFloat(Word::ZERO, Word::ZERO); // or throw
        }
        // std::cout << exponent_divmod.first.to_int32() << '\n';
        // std::cout << exponent_divmod.second.to_int32() << '\n';

        TerFloat m(significand, Word::ZERO);

        // Initial guess from lookup table
        TerFloat y(RSQRT_LOOKUP_TABLE[(significand.shr_int8(10)).to_int32() - 81], Word::from_int32(-1));

        // One newton iteration
        y = y * (TerFloat::THREE_HALVES - (m * TerFloat::HALF * y * y));
        // y = y * (TerFloat::THREE_HALVES - (m * TerFloat::HALF * y * y));

        //  Need to correctly scale result at the end
        std::pair<Word, Word> exponent_divmod = exponent.divmod(Word::TWO);
        
        TerFloat result (y.significand, y.exponent-(exponent_divmod.first));
         // Odd exponent
        if (exponent_divmod.second != Word::ZERO) {
            result = result * TerFloat::from_double(std::sqrt(1.0/3.0));
        }
        return result;
    }

    TerFloat TerFloat::sqrt() const {
        return *this * rsqrt();
    }

    double TerFloat::to_double() const {
        return significand.to_int32() * std::pow(3.0, exponent.to_int32() - 14.0);
    }

    TerFloat TerFloat::floor() const {
        return TerFloat::from_double(std::floor(to_double()));
    }


    TerFloat TerFloat::sin() const {
        if (is_inf_or_nan()) return TerFloat::NAN_;


        TerFloat x = operator%(TerFloat::TWO_PI);

        // Put into [-pi, pi]
        if (x > TerFloat::PI) {
            x = x - TerFloat::TWO_PI;
        }
        else if (x < -TerFloat::PI) {
            x = x + TerFloat::TWO_PI;
        }

        // Use symmetry to put into [-pi/2, pi/2]
        if (x > TerFloat::HALF_PI) {
            x = TerFloat::PI - x;
        }
        else if (x < TerFloat::HALF_PI) {
            x = -TerFloat::PI - x;
        }

        TerFloat x2 = x * x;
        TerFloat t1 = x;
        TerFloat t3 = t1 * x2 * TerFloat::from_double(-1.0 / 6.0);      // -x^3/6
        TerFloat t5 = t3 * x2 * TerFloat::from_double(-1.0 / 20.0); // x^5/120
        TerFloat t7 = t5 * x2 * TerFloat::from_double(-1.0 / 42.0); // -x^7/5040
        TerFloat t9 = t7 * x2 * TerFloat::from_double(-1.0 / 72.0); // x^9/362880 
        TerFloat t11 = t9 * x2 * TerFloat::from_double(-1.0 / 110.0); // -x^11/39916800 

        return t1 + t3 + t5 + t7 + t9 + t11;
    }



    TerFloat TerFloat::cos() const {
        if (is_inf_or_nan()) return TerFloat::NAN_;

        static const TerFloat PI = TerFloat::from_double(3.14159265358979323846);
        static const TerFloat TWO_PI = TerFloat::from_double(6.28318530717958647692);
        static const TerFloat HALF_PI = TerFloat::from_double(1.57079632679489661923);

        TerFloat x = operator%(TWO_PI);

        // Put into [-pi, pi]
        if (x > TerFloat::PI) {
            x = x - TerFloat::TWO_PI;
        }
        else if (x < -TerFloat::PI) {
            x = x + TerFloat::TWO_PI;
        }

        // Use symmetry to put into [-pi/2, pi/2]
        if (x > TerFloat::HALF_PI) {
            x = TerFloat::PI - x;
        }
        else if (x < TerFloat::HALF_PI) {
            x = -TerFloat::PI - x;
        }

        TerFloat x2 = x * x;
        TerFloat t0 = TerFloat::ONE;
        TerFloat t2 = x2 * TerFloat::from_double(-1.0 / 2.0);      // -x^2/2
        TerFloat t4 = t2 * x2 * TerFloat::from_double(-1.0 / 12.0); // x^4/24
        TerFloat t6 = t4 * x2 * TerFloat::from_double(-1.0 / 30.0); // -x^6/720
        TerFloat t8 = t6 * x2 * TerFloat::from_double(-1.0 / 56.0); // x^8/40320
        TerFloat t10 = t8 * x2 * TerFloat::from_double(-1.0 / 90.0); // -x^11/3628800

        return t0 + t2 + t4 + t6 + t8 + t10;
    }

    TerFloat TerFloat::tan() const {
        if (is_inf_or_nan()) {
            return TerFloat::NAN_;
        }
        return sin() / cos();
    }

    TerFloat TerFloat::atan() const {
        TerFloat x = *this;
        if (is_inf_or_nan()) {
            return TerFloat::NAN_;
        }
        if (significand == Word::ZERO) {
            return TerFloat::ZERO;
        }
        if (significand < Word::ZERO) {
            return -operator-().atan();
        }
        else if (x > TerFloat::ONE) {
            return TerFloat::HALF_PI - rec().atan();
        }
        else if (x > TerFloat::SQRT2_MINUS_1) {
            return QUARTER_PI + ((x - TerFloat::ONE) / (x + TerFloat::ONE)).atan();
        }
        else {
            TerFloat x2 = x * x;


            // Coefficients computed by me using scipy curve fit with a huge amount of data points
            // because taylor series is too slow
            // (only odd terms)
            TerFloat t1 = x * TerFloat::from_double(0.99998007); // 0.99998007x
            TerFloat t3 = t1 * x2 * TerFloat::from_double(-0.33270115073); // -0.33269452x^3
            TerFloat t5 = t3 * x2 * TerFloat::from_double(-0.58317936826); // 0.19402058x^5
            TerFloat t7 = t5 * x2 * TerFloat::from_double(-0.6066219367); // -0.11769714x^7
            TerFloat t9 = t7 * x2 * TerFloat::from_double(-0.45952696896); // 0.05408501x^9
            TerFloat t11 = t9 * x2 * TerFloat::from_double(-0.2274327027); // -0.0123007^11
            return t1 + t3 + t5 + t7 + t9 + t11;
        }
    }


    TerFloat TerFloat::exp() const {
        if (*this == TerFloat::NEGATIVE_INFINITY) {
            return TerFloat::ZERO;
        }
        else if (*this == TerFloat::POSITIVE_INFINITY) {
            return TerFloat::POSITIVE_INFINITY;
        }
        else if (is_nan()) {
            return TerFloat::NAN_;
        }

        if (significand < Word::ZERO) {
            return operator-().exp().rec();
        }
        if (operator>(TerFloat::HALF)) {
            TerFloat temp = operator/(TerFloat::from_double(2.0)).exp();
            return temp * temp;
        }
        // Taylor serises iteration
        TerFloat x = *this;

        // Doing new homer style evaluation
        TerFloat p = TerFloat::from_double(1.0 / 10.0);

        for (int k = 9; k >= 1; --k) {
            p = TerFloat::ONE + x * p / TerFloat::from_double((double)k);
        }

        return p;
    }


// TerFloat TerFloat::log() const {
//     if (*this == TerFloat::ZERO) return TerFloat::NEGATIVE_INFINITY;
//     if (significand < Word::ZERO || is_nan()) return TerFloat::NAN_;
//     if (*this == TerFloat::POSITIVE_INFINITY) return TerFloat::POSITIVE_INFINITY;

//     TerFloat m(significand, Word::ZERO);
//     TerFloat e = TerFloat::from_double((double)exponent.to_int32());

//     TerFloat u = (m - TerFloat::ONE) / (m + TerFloat::ONE);
//     TerFloat u2 = u * u;

//     TerFloat term = u;
//     TerFloat sum = term;

//     term = term * u2;
//     sum = sum + term * TerFloat::from_double(1.0 / 3.0);

//     term = term * u2;
//     sum = sum + term * TerFloat::from_double(1.0 / 5.0);

//     term = term * u2;
//     sum = sum + term * TerFloat::from_double(1.0 / 7.0);

//     term = term * u2;
//     sum = sum + term * TerFloat::from_double(1.0 / 9.0);

//     TerFloat logm = sum * TerFloat::from_double(2.0);

//     return logm + e * TerFloat::from_double(1.0986122886681098);
// }

    TerFloat TerFloat::log() const {
        if (significand == Word::ZERO) {
            return TerFloat::NEGATIVE_INFINITY;
        }
        else if (significand < Word::ZERO || is_inf_or_nan()) {
            return TerFloat::NAN_;
        }

        if (to_double() >= 3.0) {
            return TerFloat(significand, exponent - Word::ONE).log() + TerFloat::from_double(std::log(3.0));
        }
                if (to_double() < 1.0) {
            return TerFloat(significand, exponent + Word::ONE).log() - TerFloat::from_double(std::log(3.0));
        }
        
        // *this is now in [1,3)
        // Taylor series of ln(x) at x=2
        
        TerFloat xMinusA = operator-(TerFloat::from_double(2.0));
        TerFloat t0 = TerFloat::from_double(0.6931471805599453);
        TerFloat t1 = TerFloat::from_double(1.0/2.0) * xMinusA; // 1/2(x-2)
        TerFloat t2 = TerFloat::from_double(-1.0/4.0) * xMinusA * t1; // -1/8(x-2)^2
        TerFloat t3 = TerFloat::from_double(-1.0/3.0) * xMinusA * t2; // 1/24(x-2)^3
        TerFloat t4 = TerFloat::from_double(-3.0/8.0) * xMinusA * t3; // -1/64(x-2)^4
        TerFloat t5 = TerFloat::from_double(-2.0/5.0) * xMinusA * t4; // 1/160(x-2)^5
        TerFloat t6 = TerFloat::from_double(-5.0/12.0) * xMinusA * t5; // -1/384(x-2)^6
        TerFloat t7 = TerFloat::from_double(-3.0/7.0) * xMinusA * t6; // 1/896(x-2)^7
        TerFloat t8 = TerFloat::from_double(-7.0/16.0) * xMinusA * t7;// -1/2048(x-2)^8

        return t0 + t1 + t2 + t3 + t4 + t5 + t6 + t7 + t8;
    }

    TerFloat TerFloat::abs() const {
        if (significand < Word::ZERO) {
            return operator-();
        }
        else {
            return *this;
        }
    }

    TerFloat TerFloat::operator-() const {
        return TerFloat(-significand, exponent);
    }

    bool TerFloat::is_nan() const {
        return exponent.to_int32() == 21523360 && significand != Word::NEG_MIN_FLOAT_SIG && significand != Word::MIN_FLOAT_SIG;
    }

    bool TerFloat::is_inf() const {
        return exponent.to_int32() == 21523360 && (significand == Word::NEG_MIN_FLOAT_SIG || significand == Word::MIN_FLOAT_SIG);
    }

    bool TerFloat::is_finite() const {
        return exponent.to_int32() != 21523360;
    }

    bool TerFloat::is_inf_or_nan() const {
        return exponent.to_int32() == 21523360;
    }

    bool TerFloat::operator==(const TerFloat& other) const {
        return exponent == other.exponent && significand == other.significand;
    }

    bool TerFloat::operator!=(const TerFloat& other) const {
        return exponent != other.exponent || significand != other.significand;
    }

    bool TerFloat::operator<(const TerFloat& other) const {
        return operator-(other).significand < Word::ZERO;
    }


    bool TerFloat::operator<=(const TerFloat& other) const {
        return operator-(other).significand <= Word::ZERO;
    }

    bool TerFloat::operator>(const TerFloat& other) const {
        return operator-(other).significand > Word::ZERO;
    }


    bool TerFloat::operator>=(const TerFloat& other) const {
        return operator-(other).significand >= Word::ZERO;
    }

    std::string TerFloat::to_str() const {
        if (*this == TerFloat::POSITIVE_INFINITY) {
            return "inf";
        }
        else if (*this == TerFloat::NEGATIVE_INFINITY) {
            return "-inf";
        }
        else if (is_nan()) {
            return "nan";
        }
        if (significand == Word::ZERO) {
            return "0.000000";
        }
        double double_val = to_double();
        if (!std::isinf(double_val) && double_val != 0 && double_val < 1e+21 && double_val > -1e+21) {
            return std::to_string(double_val);
        }
        else {
            double log10_val = ((double)(exponent.to_int32()) * std::log10(3)) + std::log10((double)(significand.to_int32()) / 4782969.0);
            double decimal_exp = std::floor(log10_val);
            double decimal_sig = std::pow(10.0, log10_val - decimal_exp);
            if (decimal_exp > 0) {
                return std::to_string(decimal_sig) + "e+" + std::to_string((int)decimal_exp);
            }
            else {
                return std::to_string(decimal_sig) + "e-" + std::to_string((int)(-decimal_exp));
            }
        }
    }

}