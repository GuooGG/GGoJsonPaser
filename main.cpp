#include<iostream>
using namespace std;

#include"json/json.h"
#include"json/parser.h"
using namespace GGo::Json;
int main() {
	//std::cout << "hello json!" << std::endl;
	//基本类型转换成json构造函数
	//Json v1;
	//Json v2 = true;
	//Json v3 = 3;
	//Json v4 = "json4";
	//Json v5 = 5.5;

	//int a3 = v3;
	//bool a2 = v2;
	//string a4 = v4;
	//double a5 = v5;
	//
	//Json arr;
	//Json arr2;
	//arr[0] = true;
	//arr[1] = 123;
	//arr.append(1.23);
	//arr.append("hello,world!");
	//arr2[0] = false;
	//arr2[1] = 234;
	//arr2[2] = 3.56;
	//arr.append(arr2);
	////bool b = arr[0];
	////int i = arr[1];
	////double f = arr[2];
	////const string& s = arr[3];	
	Json obj;
	obj["bool"] = true;
	obj["int"] = 123;
	obj["double"] = 1.23f;
	obj["str"] = "hello obj!";
	//arr.append(obj);
	//string json = obj.str();
	////cout << json << endl;

	Json arr;
	Json arr2(json_array);
	arr[0] = 1;
	arr2.append(1);
	arr2.append(2);
	arr2.append(3);
	arr2.append("hello");
	arr.append(arr2);
	arr.append(obj);

	string json = R"({
 "kvimpex": {
  "ptazi": {
   "gdxlgdpxgvn": 446260519.5504817,
   "efronjzg": {
    "sapmfiwrrcy": [
     -641918425.3115323,
     604237256,
     371587144.08257097,
     [
      "I5UBNlCO",
      1820862718.288156,
      {
       "oyzxa": 1863704573.6049485,
       "htsbmndoem": false
      },
      {
       "bibdu": "dgo00_8zHxg9QqbH",
       "mnfgcqg": false
      },
      "aP"
     ],
     [
      true,
      {
       "xbsshakthpp": false
      },
      "u3kEbK9pBxF6",
      "gSyRG1NIU24uPev87zN",
      {
       "vmkmmc": -921962865,
       "vrmrzv": true,
       "qjvmyry": true,
       "hbvcbagdcbne": "6F7FXuB0I_GkDlW",
       "ekjwdvl": -838004413.2310606
      }
     ]
    ],
    "ewvefwr": {
     "rgvee": true
    },
    "ccqybr": -1568944420.294646
   },
   "ltzww": true,
   "osbnhmgcsz": "3Ra7",
   "csoelgyb": false,
   "fsdeqg": [
    false,
    [
     "sT2Crt",
     "jSOgYyTidHV0O54N8B",
     -1194447986.9408975,
     -1883312611
    ],
    "fm",
    {
     "mnnxda": [
      "gGStnVtopi9O6V8wwqNY",
      "wlB"
     ],
     "knqhkcvghni": {
      "fmqnyh": "JhvSH4WVD",
      "qtobqerbh": [
       false,
       false,
       false
      ],
      "vbjuykrekvbs": "2NMxbap2gbIGfj",
      "bpyxlap": {
       "ziqetnw": 230732197,
       "guyff": true,
       "xylgwzkqyx": false,
       "nvwpeoj": "Ul8SYtOMRiTFf",
       "xyhtunvsxof": "HNqiicL2xrPaiQPK"
      },
      "mgdwaywomn": [
       true,
       "KoQdE4mNG2QHmuR",
       true,
       "4ZtNVJS9Nrv60",
       false
      ],
      "ebefofhgla": -1322999522
     },
     "imyrvm": {
      "fqbdev": {
       "jloaujbbayl": "F17Wzub",
       "oiyiuz": false
      }
     },
     "fjrcvremty": "J6fL8_oN-gLS5jw",
     "jqzcbvn": [
      true,
      [
       "lmZB_VwKbv",
       "la",
       "nChdpSP_vVJfbX"
      ],
      [
       false,
       -1028052634.4861542,
       443480134.2230467,
       208256113.9070968
      ],
      "ZIwk"
     ],
     "hlijid": -1758287759
    },
    "Ovhk-oDy1hW47"
   ],
   "otlfnkya": 448591342
  },
  "fqovzkfnadaz": {
   "evfwfgciyqj": 706063097,
   "waifjuhv": {
    "agjrpy": [
     "z2E",
     -506879717.53587306,
     [
      true,
      "3puP4A",
      false,
      [
       "ynBXBasnJKFXZs0bwgpm",
       "_OHhOmY",
       true
      ]
     ],
     568722025
    ],
    "wdpcm": [
     819150228
    ],
    "gxwjzlze": -838138369,
    "qlzrnlwwj": [
     true,
     "uLupjG4GLqf0gxhJs",
     "SVtRAf3_NYacIDEgqAL",
     -681803472.2687069,
     {
      "tqtmos": false,
      "undcuwacfd": true,
      "uzryc": {
       "knfesknuojf": "_65pzE3PFsyD",
       "vxjoqtcjfqgu": -898957725.2194326,
       "ykjnxqorn": "AjC9N",
       "fktemffqd": "1o9yQuzaIzIMCxqnCe1F",
       "holemk": 112164878.49645853,
       "wjozvr": -647546340.7476213
      },
      "viizcaivjlq": true,
      "aksypyenbj": [
       "OwlXGTkOGAMxaQvLaPwG",
       1785914758.835459,
       "eOTZ1TQV"
      ],
      "hxwtcyv": {
       "aruuflin": "5p5l0jnMs27xLiuZGT",
       "zffbagpotk": "PeeD3iVZUy31TS77n",
       "phycvl": true,
       "bcfitvnkogyv": 1461309368.3309746,
       "toixim": false,
       "xruugsdwa": -1385170125,
       "cjbtimz": "pwy"
      }
     },
     -291020009.46152675,
     {
      "buyzkjlefjlb": {
       "mpvtvlbz": "6YArQQ5B2c6"
      },
      "alzpxv": false,
      "lfxyo": [
       true,
       1148610009.122615,
       2055830211.5387652
      ],
      "rmuils": [
       1864317799,
       "Le",
       331958228,
       "lX",
       true,
       1017049976.6389138
      ]
     }
    ]
   },
   "azahrvtvoti": "yvIm",
   "minaiqfuft": {
    "rkulcwwg": [
     -1529019083,
     false,
     {
      "tidjnv": true,
      "zeajfaimd": -919068886.9005436,
      "qxbkpi": false,
      "ilxrurmvh": false,
      "ouxtnrcywexm": false,
      "aorlohr": false,
      "eujdphoihiow": [
       true,
       false,
       "lyzjGLEpApe",
       -1449293747,
       "dvRowGAIa_R",
       false,
       "7"
      ]
     },
     [
      [
       "Jtrc1QK",
       true,
       "80HzyusLb_"
      ],
      [
       false,
       -709570744.974451,
       false,
       true
      ],
      [
       "HSGG0SC",
       true,
       "WBLtS6vu_DGBRFFqh"
      ],
      true
     ],
     [
      "QlI",
      [
       2118391587,
       true,
       "cY_vPQi",
       false
      ],
      [
       "F"
      ],
      "mj",
      true,
      {
       "ikhkidncnamp": "K"
      }
     ],
     {
      "gbyrxroez": {
       "hsgcd": "DO",
       "egxhikqqxt": "Q8oZGKoSQaaXylqzEu",
       "gqgaprfjt": "11n",
       "ejypwq": "ER5Xh2Is",
       "eiepcemfx": true,
       "stewkxmzs": "zU",
       "sipcaq": true
      },
      "jsydkkoa": -2123728407.975219
     }
    ],
    "myjgrbxghess": {
     "myfkirhnmjuk": 653910688,
     "tqfsscfkg": 1042234726.6927112,
     "cfukbvosyxa": 774523114,
     "pkdeqwsneial": {
      "vmsiedcbd": [
       1558045869.2760673,
       "7M8",
       false,
       false,
       1251709268,
       "6XAasfR",
       "nlUCQudcJs"
      ],
      "yyjbz": {
       "sunjve": "qlHPQ8u"
      },
      "mrqohhvd": [
       2071834991,
       true,
       true,
       false
      ],
      "hyhraw": "Manfqk6ZLUao008q",
      "thfki": {
       "gbxqi": "RJbFE5",
       "kbgpuxrs": "F1ZPwhAPEJ0WIOiJ",
       "hnrevpvu": "jeiiETwQReD2q3x1Ex",
       "luqxgtoccr": "KmuD8OiRoHquQ4R6Fz"
      }
     },
     "elvmajb": "4y-9JS0EOBdTo0",
     "ipoavrcqzc": "atwrjmyPW0xu3KNKW"
    },
    "zvtnccucvhl": {
     "bzlgx": [
      [
       334925587.2162043,
       "c-0s-QVnHWvSJk_",
       true,
       false,
       -628787626.5398118
      ],
      "lTXZb",
      {
       "vvwdoztglemr": "niO3e",
       "muomsmojjkyt": -2111151593,
       "fmxdkc": 1471503672,
       "rwqjxhenrb": 1320840442.7614055,
       "ycercuqhicru": "Ajp8mBw0Ac"
      },
      -1547908065,
      "YwAaCaC8a6WwcyJ1k",
      1908998277.9095464
     ]
    },
    "ilwnelwpni": false,
    "dcpkzhlpr": false,
    "pjdjbgy": "ViDW3Vf"
   },
   "vfotdvyna": 1602180424
  },
  "xcjtybfcqck": "r",
  "ijmjri": true
 }
})";



	//测试json解析器代码
	Parser parser;
	parser.load(json);
	Json parsed = parser.Parse();
	//cout << json << endl;
	cout << parsed.str();
	return 0;
}