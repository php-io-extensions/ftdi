<?php

namespace Zephir\Optimizers\FunctionCall;

use Zephir\Call;
use Zephir\CompilationContext;
use Zephir\CompiledExpression;
use Zephir\Exception\CompilerException;
use Zephir\Optimizers\OptimizerAbstract;

class FtdiReadChipIdOptimizer extends OptimizerAbstract
{
    public function optimize(array $expression, Call $call, CompilationContext $context)
    {
        if (!isset($expression['parameters']) || count($expression['parameters']) !== 1) {
            throw new CompilerException("'ftdi_read_chip_id' requires exactly one parameter", $expression);
        }

        [$symbolVariable, $resolvedParams, $symbol] = $this->processStringOptimizer(
            $call,
            $context,
            $expression
        );

        $context->headersManager->add('api/ftdi-eeprom');

        $context->codePrinter->output(
            'ftdi_read_chip_id(' . $symbol . ', ' . $resolvedParams[0] . ');'
        );

        return new CompiledExpression('variable', $symbolVariable->getRealName(), $expression);
    }
}
