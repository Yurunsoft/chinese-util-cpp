<?php

class SwoolePinyinTest extends PinyinTest
{
    protected $methodPrefix = 'swoole_';

    protected function check()
    {
        if(!extension_loaded('Swoole'))
        {
            $this->markTestSkipped('You must enable Swoole extension');
        }
    }

    protected function call(callable $callable)
    {
        \Co\run($callable);
    }

}
