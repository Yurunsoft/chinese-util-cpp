<?php

use PHPUnit\Framework\TestCase;

class PinyinTest extends TestCase
{
    protected $methodPrefix = '';

    protected function check()
    {

    }

    protected function call(callable $callable)
    {
        $callable();
    }

    protected function parseLine($string)
    {
        return str_replace(PHP_EOL, "\n", $string);
    }

    /**
     * @testdox pinyin-1
     *
     * @return void
     */
    public function testPinyin1()
    {
        $this->check();
        $this->call(function(){
            ob_start();
            var_dump(($this->methodPrefix . 'convert_to_pinyin_array')('恭喜發財！123', 15));
            $this->assertEquals($this->parseLine(<<<EXPECTED
array(4) {
  ["pinyin"]=>
  array(1) {
    [0]=>
    array(8) {
      [0]=>
      string(4) "gong"
      [1]=>
      string(2) "xi"
      [2]=>
      string(2) "fa"
      [3]=>
      string(3) "cai"
      [4]=>
      string(3) "！"
      [5]=>
      string(1) "1"
      [6]=>
      string(1) "2"
      [7]=>
      string(1) "3"
    }
  }
  ["pinyinSound"]=>
  array(1) {
    [0]=>
    array(8) {
      [0]=>
      string(5) "gōng"
      [1]=>
      string(3) "xǐ"
      [2]=>
      string(3) "fā"
      [3]=>
      string(4) "cái"
      [4]=>
      string(3) "！"
      [5]=>
      string(1) "1"
      [6]=>
      string(1) "2"
      [7]=>
      string(1) "3"
    }
  }
  ["pinyinSoundNumber"]=>
  array(1) {
    [0]=>
    array(8) {
      [0]=>
      string(5) "gong1"
      [1]=>
      string(3) "xi3"
      [2]=>
      string(3) "fa1"
      [3]=>
      string(4) "cai2"
      [4]=>
      string(3) "！"
      [5]=>
      string(1) "1"
      [6]=>
      string(1) "2"
      [7]=>
      string(1) "3"
    }
  }
  ["pinyinFirst"]=>
  array(1) {
    [0]=>
    array(8) {
      [0]=>
      string(1) "g"
      [1]=>
      string(1) "x"
      [2]=>
      string(1) "f"
      [3]=>
      string(1) "c"
      [4]=>
      string(3) "！"
      [5]=>
      string(1) "1"
      [6]=>
      string(1) "2"
      [7]=>
      string(1) "3"
    }
  }
}

EXPECTED
    ), ob_get_clean());
        });
    }

    /**
     * @testdox pinyin-2
     *
     * @return void
     */
    public function testPinyin2()
    {
        $this->check();
        $this->call(function(){
            ob_start();
            var_dump(($this->methodPrefix . 'convert_to_pinyin_array')('我的', 15));
            $this->assertEquals($this->parseLine(<<<EXPECTED
array(4) {
  ["pinyin"]=>
  array(2) {
    [0]=>
    array(2) {
      [0]=>
      string(2) "wo"
      [1]=>
      string(2) "di"
    }
    [1]=>
    array(2) {
      [0]=>
      string(2) "wo"
      [1]=>
      string(2) "de"
    }
  }
  ["pinyinSound"]=>
  array(3) {
    [0]=>
    array(2) {
      [0]=>
      string(3) "wǒ"
      [1]=>
      string(3) "dí"
    }
    [1]=>
    array(2) {
      [0]=>
      string(3) "wǒ"
      [1]=>
      string(3) "dì"
    }
    [2]=>
    array(2) {
      [0]=>
      string(3) "wǒ"
      [1]=>
      string(2) "de"
    }
  }
  ["pinyinSoundNumber"]=>
  array(3) {
    [0]=>
    array(2) {
      [0]=>
      string(3) "wo3"
      [1]=>
      string(3) "di2"
    }
    [1]=>
    array(2) {
      [0]=>
      string(3) "wo3"
      [1]=>
      string(3) "di4"
    }
    [2]=>
    array(2) {
      [0]=>
      string(3) "wo3"
      [1]=>
      string(3) "de0"
    }
  }
  ["pinyinFirst"]=>
  array(1) {
    [0]=>
    array(2) {
      [0]=>
      string(1) "w"
      [1]=>
      string(1) "d"
    }
  }
}

EXPECTED
    ), ob_get_clean());
        });
    }

    /**
     * @testdox 全拼
     *
     * @return void
     */
    public function testPinyinAll()
    {
        $this->check();
        $this->call(function(){
            ob_start();
            var_dump(($this->methodPrefix . 'convert_to_pinyin_array')('恭喜發財！123', 1));
            $this->assertEquals($this->parseLine(<<<EXPECTED
array(1) {
  ["pinyin"]=>
  array(1) {
    [0]=>
    array(8) {
      [0]=>
      string(4) "gong"
      [1]=>
      string(2) "xi"
      [2]=>
      string(2) "fa"
      [3]=>
      string(3) "cai"
      [4]=>
      string(3) "！"
      [5]=>
      string(1) "1"
      [6]=>
      string(1) "2"
      [7]=>
      string(1) "3"
    }
  }
}

EXPECTED
    ), ob_get_clean());
        });
    }

    /**
     * @testdox 拼音首字母
     *
     * @return void
     */
    public function testPinyinFirst()
    {
        $this->check();
        $this->call(function(){
            ob_start();
            var_dump(($this->methodPrefix . 'convert_to_pinyin_array')('恭喜發財！123', 8));
            $this->assertEquals($this->parseLine(<<<EXPECTED
array(1) {
  ["pinyinFirst"]=>
  array(1) {
    [0]=>
    array(8) {
      [0]=>
      string(1) "g"
      [1]=>
      string(1) "x"
      [2]=>
      string(1) "f"
      [3]=>
      string(1) "c"
      [4]=>
      string(3) "！"
      [5]=>
      string(1) "1"
      [6]=>
      string(1) "2"
      [7]=>
      string(1) "3"
    }
  }
}

EXPECTED
    ), ob_get_clean());
        });
    }

    /**
     * @testdox 读音
     *
     * @return void
     */
    public function testPinyinSound()
    {
        $this->check();
        $this->call(function(){
            ob_start();
            var_dump(($this->methodPrefix . 'convert_to_pinyin_array')('恭喜發財！123', 2));
            $this->assertEquals($this->parseLine(<<<EXPECTED
array(1) {
  ["pinyinSound"]=>
  array(1) {
    [0]=>
    array(8) {
      [0]=>
      string(5) "gōng"
      [1]=>
      string(3) "xǐ"
      [2]=>
      string(3) "fā"
      [3]=>
      string(4) "cái"
      [4]=>
      string(3) "！"
      [5]=>
      string(1) "1"
      [6]=>
      string(1) "2"
      [7]=>
      string(1) "3"
    }
  }
}

EXPECTED
    ), ob_get_clean());
        });
    }

    /**
     * @testdox 读音数字
     *
     * @return void
     */
    public function testPinyinSoundNumber()
    {
        $this->check();
        $this->call(function(){
            ob_start();
            var_dump(($this->methodPrefix . 'convert_to_pinyin_array')('恭喜發財！123', 4));
            $this->assertEquals($this->parseLine(<<<EXPECTED
array(1) {
  ["pinyinSoundNumber"]=>
  array(1) {
    [0]=>
    array(8) {
      [0]=>
      string(5) "gong1"
      [1]=>
      string(3) "xi3"
      [2]=>
      string(3) "fa1"
      [3]=>
      string(4) "cai2"
      [4]=>
      string(3) "！"
      [5]=>
      string(1) "1"
      [6]=>
      string(1) "2"
      [7]=>
      string(1) "3"
    }
  }
}

EXPECTED
    ), ob_get_clean());
        });
    }

    /**
     * @testdox 自选返回格式 + 以文本格式返回 + 自定义分隔符
     *
     * @return void
     */
    public function testPinyinCustom()
    {
        $this->check();
        $this->call(function(){
            ob_start();
            var_dump(($this->methodPrefix . 'convert_to_pinyin_string')('恭喜發財！123', 1 | 4, true, ' '));
            $this->assertEquals($this->parseLine(<<<EXPECTED
array(2) {
  ["pinyin"]=>
  array(1) {
    [0]=>
    string(24) "gong xi fa cai ！ 1 2 3"
  }
  ["pinyinSoundNumber"]=>
  array(1) {
    [0]=>
    string(28) "gong1 xi3 fa1 cai2 ！ 1 2 3"
  }
}

EXPECTED
    ), ob_get_clean());
        });
    }

    /**
     * @testdox 分割无拼音字符
     *
     * @return void
     */
    public function testPinyinSplitNoPinyin()
    {
        $this->check();
        $this->call(function(){
            ob_start();
            var_dump(($this->methodPrefix . 'convert_to_pinyin_string')('恭喜發財！123', 1, true, '-'));
            $this->assertEquals($this->parseLine(<<<EXPECTED
array(1) {
  ["pinyin"]=>
  array(1) {
    [0]=>
    string(24) "gong-xi-fa-cai-！-1-2-3"
  }
}

EXPECTED
    ), ob_get_clean());
        });
    }

    /**
     * @testdox 不分割无拼音字符
     *
     * @return void
     */
    public function testPinyinNotSplitNoPinyin()
    {
        $this->check();
        $this->call(function(){
            ob_start();
            var_dump(($this->methodPrefix . 'convert_to_pinyin_string')('恭喜發財！123', 1, false, '-'));
            $this->assertEquals($this->parseLine(<<<EXPECTED
array(1) {
  ["pinyin"]=>
  array(1) {
    [0]=>
    string(21) "gong-xi-fa-cai-！123"
  }
}

EXPECTED
    ), ob_get_clean());
        });
    }

    /**
     * @testdox 拼音分词
     *
     * @return void
     */
    public function testPinyinSplit()
    {
        $this->check();
        $this->call(function(){
            $this->assertEquals([
                ['xiang', 'gang'],
                ['xi', 'ang', 'gang'],
            ], ($this->methodPrefix . 'split_pinyin_array')('xianggang'));

            $this->assertEquals([
                'xiang gang',
                'xi ang gang',
            ], ($this->methodPrefix . 'split_pinyin_string')('xianggang'));

            $this->assertEquals([
                's b te lang pu s b',
            ], ($this->methodPrefix . 'split_pinyin_string')('sbtelangpusb'));
        
            $this->assertEquals([
                '啊 xian',
                '啊 xi an',
            ], ($this->methodPrefix . 'split_pinyin_string')('啊xian'));
        
            $this->assertEquals([
                'xi 啊 an',
            ], ($this->methodPrefix . 'split_pinyin_string')('xi啊an'));
        
            $this->assertEquals([
                'xian 啊',
                'xi an 啊',
            ], ($this->methodPrefix . 'split_pinyin_string')('xian啊'));
        
            $this->assertEquals([
                '一 xian 二',
                '一 xi an 二',
            ], ($this->methodPrefix . 'split_pinyin_string')('一xian二'));
        
            $this->assertEquals([
                '一 xi 二 an 三',
            ], ($this->methodPrefix . 'split_pinyin_string')('一xi二an三'));
        });
    }

    /**
     * @testdox 简繁互转
     *
     * @return void
     */
    public function testSimplifiedAndTraditional()
    {
        $this->check();
        $this->call(function(){
            $simplified = '中华人民共和国！恭喜发财！';
            $traditional = '中華人民共和國！恭喜發財！';
            $this->assertEquals([$traditional, '中華人民共和國！恭喜髮財！'], ($this->methodPrefix . 'convert_to_traditional')($simplified));
            $this->assertEquals([$simplified], ($this->methodPrefix . 'convert_to_simplified')($traditional));
        });
    }

    public function testNumberToChinese()
    {
        $this->check();
        // 数字
        $this->assertEquals('五', ($this->methodPrefix . 'convert_number_to_chinese')(5));
        $this->assertEquals('一十二', ($this->methodPrefix . 'convert_number_to_chinese')(12));

        // 过滤一十二的一
        $this->assertEquals('五', ($this->methodPrefix . 'convert_number_to_chinese')(5, true));
        $this->assertEquals('十二', ($this->methodPrefix . 'convert_number_to_chinese')(12, true));

        // 负数
        $this->assertEquals('负五', ($this->methodPrefix . 'convert_number_to_chinese')(-5));

        // 小数
        $this->assertEquals('三点一四一五', ($this->methodPrefix . 'convert_number_to_chinese')(3.1415));

    }

    public function testNumberToNumber()
    {
        $this->check();
        // 数字
        $this->assertEquals(5, ($this->methodPrefix . 'convert_chinese_to_number')('五'));
        $this->assertEquals(12, ($this->methodPrefix . 'convert_chinese_to_number')('一十二'));
        $this->assertEquals(12, ($this->methodPrefix . 'convert_chinese_to_number')('十二'));

        // 负数
        $this->assertEquals(-5, ($this->methodPrefix . 'convert_chinese_to_number')('负五'));

        // 小数
        $this->assertEquals(3.1415, ($this->methodPrefix . 'convert_chinese_to_number')('三点一四一五'));
    }

    public function testMoneyToChinese()
    {
        $this->check();
        // 数字
        $this->assertEquals('伍圆', ($this->methodPrefix . 'convert_money_to_chinese')(5));
        $this->assertEquals('壹拾贰圆', ($this->methodPrefix . 'convert_money_to_chinese')(12));

        // 负数
        $this->assertEquals('负伍圆', ($this->methodPrefix . 'convert_money_to_chinese')(-5));

        // 小数
        $this->assertEquals('叁圆壹角肆分壹厘伍毫', ($this->methodPrefix . 'convert_money_to_chinese')(3.1415));

    }

    public function testMoneyToNumber()
    {
        $this->check();
        // 数字
        $this->assertEquals(5, ($this->methodPrefix . 'convert_chinese_to_money')('伍圆'));
        $this->assertEquals(12, ($this->methodPrefix . 'convert_chinese_to_money')('壹拾贰圆'));

        // 负数
        $this->assertEquals(-5, ($this->methodPrefix . 'convert_chinese_to_money')('负伍圆'));

        // 小数
        $this->assertEquals(3.1415, ($this->methodPrefix . 'convert_chinese_to_money')('叁圆壹角肆分壹厘伍毫'));
    }
}
